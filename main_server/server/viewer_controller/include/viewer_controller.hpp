#pragma once

#include <array>
#include <unordered_map>

#include "ViewersTable.hpp"
#include "RoomsTable.hpp"
#include "../../../include/json.hpp"
#include "session.hpp"

using json = nlohmann::json;
using session_ptr = std::shared_ptr<Session>;
using room_ptr = std::shared_ptr<Room>;
using rooms_map = std::unordered_map<std::size_t, room_ptr>;

class ViewerController {
    ViewersTable table_;
    RoomsTable room_table_;
    const std::array<std::string, 6> allowed_methods_{
        "addUserToRoom",     "deleteUserFromRoom", "getViewersInfo",
        "getUserRoleInRoom", "getUserRooms",       "getRoomUsers"};

   public:
    ViewerController(const json& request, db_ptr database, session_ptr session,
                     rooms_map& rooms);

   private:
    void AddUserToRoom(const json& data, session_ptr session, rooms_map rooms);
    void DeleteUserFromRoom(const json& data, session_ptr session,
                            rooms_map rooms);
    void GetViewersInfo(const json& data, session_ptr session);

    void GetUserRoleInRoom(session_ptr session);

    void GetUserRooms(session_ptr session);

    void GetRoomUsers(session_ptr session);
};
