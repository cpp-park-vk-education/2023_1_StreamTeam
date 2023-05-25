#pragma once

#include <unordered_map>
#include "room.hpp"
#include "boost/asio.hpp"
#include "IDatabase.hpp"
#include "RoomsTable.hpp"
#include "../../../include/json.hpp"

using json = nlohmann::json;
using db_ptr = std::shared_ptr<IDatabase>;
using room_ptr = std::shared_ptr<Room>;
using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_context& io_context, unsigned short port, db_ptr database)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), database_(database) {
        RoomsTable table(database);
        json rooms = table.getAllRooms();
        for (auto room : rooms["result"]) {
            rooms_[room["id"]] = std::make_shared<Room>(room["creator"], room["id"]);
        }
        Accept();
    }
private:
    void Accept();
    std::unordered_map<std::size_t, room_ptr> rooms_;
    tcp::acceptor acceptor_;
    unsigned short stream_port_;
    db_ptr database_;
};