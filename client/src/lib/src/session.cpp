#include "../include/session.hpp"

#include <iostream>

using boost::asio::ip::tcp;

static std::vector<std::string> Split(const std::string& src,
                                      size_t len) {
    std::vector<std::string> res;
    if (src.empty() || !len) {
        return res;
    }
    size_t pos = 0;
    size_t full_len = src.length();
    while (len < full_len - pos) {
        res.push_back(src.substr(pos, len));
        pos += len;
    }
    res.push_back(src.substr(pos, full_len - pos));
    return res;
}

Session::Session(boost::asio::io_context& io_context,
                         const tcp::resolver::results_type& endpoint)
        : io_context_(io_context), socket_(io_context) {
    Connect(endpoint);
}

std::shared_ptr<Session> Session::getInstance() {
    return session_instance_;
}

void Session::setInstance(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoint) {
    session_instance_ = std::make_shared<Session>(io_context, endpoint);
}

void Session::Send(const std::string& str, std::function<void(const nlohmann::json_abi_v3_11_2::json&)> func) {
    command_queue_.push(func);

    auto parts = Split(str, Request::max_body_length);
        for (const auto& part : parts) {
            Request msg(part);
            boost::asio::post(io_context_, [this, msg]() {
                bool write_in_progress = !queue_.empty();
                queue_.push_back(msg);
                if (!write_in_progress) {
                    Write();
                }
            });
        }
}

void Session::Close() {
    boost::asio::post(io_context_, [this]() { socket_.close(); });
}

void Session::Connect(const tcp::resolver::results_type& endpoint) {
    std::cout << "Connection" << std::endl;

    boost::asio::async_connect(
            socket_, endpoint, [this](boost::system::error_code ec, tcp::endpoint) {
                if (!ec) {
                    ReadHeader();
                } else {
                    std::cerr << ec.message() << std::endl;
                }
            });
}

void Session::ReadHeader() {
    boost::asio::async_read(
            socket_,
            boost::asio::buffer(read_msg_.data(), Request::header_length),
            [this](boost::system::error_code ec, std::size_t length) {
                if (!ec && read_msg_.decode_header()) {
                    ReadBody();
                } else {
                    socket_.close();
                }
            });
}

void Session::ReadBody() {
    boost::asio::async_read(
            socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
            [this](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    std::string body(read_msg_.body());
                    std::string response = body.substr(0, length);
                    std::cout << "From ReadBody:" <<  response << std::endl;

                    nlohmann::json_abi_v3_11_2::json answ = nlohmann::json_abi_v3_11_2::json::parse(response);

                    if (!command_queue_.empty()) {
                        auto func = command_queue_.front();
                        command_queue_.pop();
                        func(answ);
                    }

                    ReadHeader();
                } else {
                    std::cerr << ec.message() << std::endl;
                    socket_.close();
                }
            });
}

void Session::Write() {
    boost::asio::async_write(
            socket_,
            boost::asio::buffer(queue_.front().data(),
                                queue_.front().length()),
            [this](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    queue_.pop_front();
                    if (!queue_.empty()) {
                        Write();
                    }
                } else {
                    std::cerr << ec.message() << std::endl;
                    socket_.close();
                }
            });
}
