#include "ViewersTable.hpp"

#include <iostream>

ViewersTable::ViewersTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json ViewersTable::getUserRooms(const size_t id_user) const
{
    json request = {{"id", id_user}};
    json response = client->select(request);
    return response;
}

json ViewersTable::getRoomUsers(const size_t id_room) const
{
    json request = {{"id", id_room}};
    json response = client->select(request);
    return response;
}

json ViewersTable::addUserToRoom(const size_t id_user, const size_t id_room) const
{
    json request = {{{"id_user", id_user},
                     {"id_room", id_room}}};
    json response = client->insert(request);
    return response;
}

json ViewersTable::getUserPointsInRoom(const size_t id_user, const size_t id_room) const
{
    json request = {{{"id_user", id_user},
                     {"id_room", id_room}}};
    json response = client->select(request);
    return response;
}

json ViewersTable::setUserPointsInRoom(const size_t id_user, const size_t id_room, const size_t points) const
{
    json request = {{{"id_user", id_user},
                     {"id_room", id_room},
                     {"points", points}}};
    json response = client->update(request);
    return response;
}

json ViewersTable::getUserRoleInRoom(const size_t id_user, const size_t id_room) const
{
    json request = {{{"id_user", id_user},
                     {"id_room", id_room}}};
    json response = client->select(request);
    return response;
}

json ViewersTable::setUserRoleInRoom(const size_t id_user, const size_t id_room, const std::string &role) const
{
    json request = {{{"id_user", id_user},
                     {"id_room", id_room},
                     {"role", role}}};
    json response = client->update(request);
    return response;
}
