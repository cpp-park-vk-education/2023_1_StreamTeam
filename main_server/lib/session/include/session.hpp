#pragma once

#include <list>
#include <string>
#include "boost/asio.hpp"
#include "iroom.hpp"
#include "router.hpp"
#include "isession.hpp"

class IRoom;
using room_ptr = std::shared_ptr<IRoom>;
class Router;
using rout_ptr = std::shared_ptr<Router>;
using boost::asio::ip::tcp;


class Session : public ISession {
public:
    Session(tcp::socket socket, room_ptr room, rout_ptr router)
        : socket_(std::move(socket)), room_(room), router_(router) {}
    void Run() override;
    void Send(const std::string& msg) override;
private:
    void Write();
    void Read();
    room_ptr room_;
    tcp::socket socket_;
    std::string buffer;
    std::list<std::string> queue_;
    rout_ptr router_;
};