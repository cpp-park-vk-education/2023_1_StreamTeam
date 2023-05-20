#pragma once

#include <array>
#include <unordered_map>

#include "RoomsTable.hpp"
#include "nlohmann/json.hpp"
#include "session.hpp"

using json = nlohmann::json;
using session_ptr = std::shared_ptr<Session>;
using room_ptr = std::shared_ptr<Room>;
using rooms_map = std::unordered_map<std::size_t, room_ptr>;

class RoomController {
    RoomsTable table_;
    const std::array<std::string, 5> allowed_methods_{
        "addRoom",     "deleteRoom",
        "updateRoom", "getRoomInfo", "getAllRooms"};

   public:
    RoomController(const json& request, db_ptr database, session_ptr session,
                   rooms_map& rooms);

   private:
    void AddRoom(const json& request, session_ptr session, rooms_map rooms);
    void DeleteRoom(const json& data, session_ptr session, rooms_map rooms);
    void GetRoomInfo(const json& data, session_ptr session);
    void UpdateRoom(const json& data, session_ptr session, rooms_map rooms);
    void GetAllRooms(session_ptr session);
};
