#pragma once

#include <unordered_set>
#include "iroom.hpp"
#include "boost/asio.hpp"

class IRoom;
using room_ptr = std::shared_ptr<IRoom>;

class IRoom;
using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_context& io_context, unsigned short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    }
private:
    void Accept();
    std::unordered_set<room_ptr> rooms_;
    tcp::acceptor acceptor_;
};