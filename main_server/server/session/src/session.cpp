#include "session.hpp"

#include <iostream>

#include "auth.hpp"
#include "film_controller.hpp"
#include "message_controller.hpp"
#include "../../../include/json.hpp"
#include "response.hpp"
#include "room_controller.hpp"
#include "user_controller.hpp"
#include "video_controller.hpp"
#include "viewer_controller.hpp"

using json = nlohmann::json;

void Session::Run() {
    Send(NotAuthorized());
    ReadHeader();
}

void Session::Send(const Message& msg) {
    bool write_in_progress = !queue_.empty();
    queue_.push_back(msg);
    if (!write_in_progress) {
        Write();
    }
}

void Session::ReadHeader() {
    auto self(shared_from_this());
    boost::asio::async_read(
        socket_, boost::asio::buffer(read_msg_.data(), Message::header_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec && read_msg_.decode_header()) {
                ReadBody();
            } else {
                std::cout << ec.message() << std::endl;
            }
        });
}

void Session::ReadBody() {
    auto self(shared_from_this());
    boost::asio::async_read(
        socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::string body(read_msg_.body());
                std::string request = body.substr(0, length);
                json req;
                try {
                    req = json::parse(request);
                    std::cout << req << "\n";
                    if (!is_auth_) {
                        try {
                            Auth(req, database_, self);
                        } catch (std::exception &err) {
                            std::cerr << "auth_err\n";
                            std::cerr << err.what() << std::endl;
                        }
                    } else {
                        Parse(req);
                    }
                } catch (json::parse_error& err) {
                    Send(BadRequest());
                    std::cerr << err.what() << std::endl;
                }
                ReadHeader();
            } else {
                std::cout << ec.message() << std::endl;
            }
        });
}

void Session::Write() {
    auto self(shared_from_this());
    boost::asio::async_write(
        socket_,
        boost::asio::buffer(queue_.front().data(), queue_.front().length()),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                queue_.pop_front();
                if (!queue_.empty()) {
                    Write();
                }
            } else {
                std::cout << ec.message() << std::endl;
            }
        });
}

void Session::SetRoomId(std::size_t id) { room_id_ = id; }

std::size_t Session::GetRoomId() { return room_id_; }

void Session::SetRoom(room_ptr room) { room_ = room; }

void Session::SetUserId(std::size_t id) { user_id_ = id; }

std::size_t Session::GetUserId() const { return user_id_; }

std::string Session::GetUserEndpoint() {
    std::stringstream stream;
    stream << socket_.remote_endpoint();
    return stream.str();
}

void Session::SetAuthorized(std::size_t id) {
    is_auth_ = true;
    user_id_ = id;
}

void Session::SetUnAuthorized() { is_auth_ = false; }

void Session::LeaveRoom() {
    auto self(shared_from_this());
    if (room_) {
        room_->Leave(self);
    }
}

bool CheckFields(const json& request, const std::vector<std::string>& fields) {
    for (const auto& field : fields) {
        if (!request.contains(field)) {
            return false;
        }
    }
    return true;
}

void Session::Parse(const json& req) {
    json request = req;
    if (!CheckFields(request, required_fields_)) {
        Send(BadRequest());
        return;
    }
    auto itr =
        std::find(allowed_tables_.begin(), allowed_tables_.end(), request["table"]);
    if (itr == allowed_tables_.end()) {
        Send(BadRequest());
        return;
    }
    std::string table = request["table"];
    request.erase("table");
    auto self(shared_from_this());
    try {
        if (table == "user") {
            UserController(request, database_, self);
        } else if (table == "room") {
            RoomController(request, database_, self, rooms_);
        } else if (table == "video") {
            VideoController(request, database_, self, room_);
        } else if (table == "message") {
            MessageController(request, database_, self, room_);
        } else if (table == "film") {
            FilmController(request, database_, self);
        } else {
            ViewerController(request, database_, self, rooms_);
        }
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}