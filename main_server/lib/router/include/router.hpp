#pragma once
#include <string>
#include "room.hpp"

class IRoom;
using room_ptr = std::shared_ptr<IRoom>;

//class IDatabase;

class Router {
public:
    std::string Authentication(const std::string& info) ;
    std::string Register(const std::string& info) ;
    std::string GetRooms(const std::string& info);
    std::string JoinRoom(room_ptr room);
    std::string LeaveRoom(room_ptr room);
    std::string SendMessage(room_ptr room, const std::string& msg);
    std::string StartVideo(const std::string& info);
    std::string PauseVideo(const std::string& info);
    void Synchronise(const std::string& info);
private:
//    std::unique_ptr<IDatabase> database_;
};