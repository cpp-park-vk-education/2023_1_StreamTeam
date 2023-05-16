#pragma once

#include <list>
#include <string>
#include <unordered_map>
#include <vector>

#include "IDatabase.hpp"
#include "boost/asio.hpp"
#include "room.hpp"
#include "message.hpp"

class Room;
using db_ptr = std::shared_ptr<IDatabase>;
using room_ptr = std::shared_ptr<Room>;
using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
   public:
    Session(tcp::socket socket, std::unordered_map<std::size_t, room_ptr>& rooms,
            unsigned short stream_port, db_ptr database)
        : socket_(std::move(socket)),
          is_auth_(false),
          rooms_(rooms),
          stream_port_(stream_port),
          database_(database) {}
    void Run();
    void Send(const Message& msg);
    void SetRoom(room_ptr room);
    void SetRoomId(std::size_t id);
    std::string GetUserEndpoint();
    std::size_t GetRoomId();
    void SetUserId(std::size_t id);
    std::size_t GetUserId() const;
    void LeaveRoom();
    void SetAuthorized(std::size_t id);
    void SetUnAuthorized();
    void Parse(const json& req);

   private:
    void Write();
    void ReadHeader();
    void ReadBody();
    room_ptr room_;
    tcp::socket socket_;
    bool is_auth_;
    std::unordered_map<std::size_t, room_ptr>& rooms_;
    std::string buffer;
    std::list<Message> queue_;
    Message read_msg_;
    std::size_t room_id_;
    std::size_t user_id_;
    unsigned short stream_port_;
    db_ptr database_;
    const std::vector<std::string> required_fields_{"table", "method", "data"};
    const std::vector<std::string> allowed_tables_{"user", "room", "viewer", "video", "message", "film"};
};