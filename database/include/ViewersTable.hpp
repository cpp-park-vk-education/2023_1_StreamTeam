#pragma once

#include "PostgreSQL.hpp"

class ViewersTable
{
public:
    ViewersTable() = default;
    ViewersTable(std::shared_ptr<IDatabase> client);

    json getUserRooms(const size_t id_user) const;
    json getRoomUsers(const size_t id_room) const;

    json addUserToRoom(const size_t id_user, const size_t id_room) const;
    json deleteUserFromRoom(const size_t id_user, const size_t id_room) const;
    json checkUserInRoom(const size_t id_user, const size_t id_room) const;
    json getViewersInfo(const size_t id) const;
    json getUserPointsInRoom(const size_t id_user, const size_t id_room) const;
    json setUserPointsInRoom(const size_t id_user, const size_t id_room, const size_t points) const;
    json getUserRoleInRoom(const size_t id_user, const size_t id_room) const;
    json setUserRoleInRoom(const size_t id_user, const size_t id_room, const std::string &role) const;

private:
    std::shared_ptr<IDatabase> client;
};
