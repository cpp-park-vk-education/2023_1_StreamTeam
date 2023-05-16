#include "video_controller.hpp"

#include <boost/asio.hpp>

#include "response.hpp"

using boost::asio::ip::tcp;

VideoController::VideoController(const json& request, db_ptr database,
                                 session_ptr session, room_ptr room,
                                 unsigned short stream_port)
    : table_(database), stream_port_(stream_port) {
    if (!room->IsOwner(session)) {
        session->Send(Forbidden());
        throw std::runtime_error{"Forbidden"};
    }
    auto itr = std::find(allowed_methods.begin(), allowed_methods.end(),
                         request["method"]);
    if (itr == allowed_methods.end()) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    FormRequest(request["method"], room, session);
}

void VideoController::FormRequest(const std::string& method, room_ptr room,
                                  session_ptr session) {
    std::size_t id = room->GetId();
    json info = table_.getCurrentFilm(id);
    info["method"] = method;
    info["endpoints"] = room->GetEndpoints();
    std::string data = info.dump();
    std::string response = SendRequest(data);
    json req_json;
    try {
        req_json = json::parse(response);
    } catch (json::parse_error& err) {
        err.what();
        session->Send(NotFound());
        throw std::runtime_error{"NotFound"};
    }
    if (req_json["status"] == "ok") {
        session->Send(Ok());
    } else {
        session->Send(NotFound());
    }
}

std::string VideoController::SendRequest(const std::string& msg) {
    boost::asio::io_context io_context;
    tcp::socket socket(io_context);
    tcp::resolver resolver(io_context);
    boost::asio::connect(socket, resolver.resolve("localhost", std::to_string(stream_port_)));
    boost::asio::write(socket, boost::asio::buffer(msg, msg.size()));
    std::array<char, 1024> reply;
    size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply));
    std::string answer(reply.begin(), reply.begin() + reply_length);
    return answer;
}
