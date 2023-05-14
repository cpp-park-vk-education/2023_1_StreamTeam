#include "ViewersTable.hpp"

#include <iostream>

ViewersTable::ViewersTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json ViewersTable::getUserRooms(const size_t id_user) const
{
    json request = {{"SELECT", {"id_room"}},
                    {"FROM", {viewersTableName}},
                    {"WHERE", {"id_user=" + std::to_string(id_user)}}};

    json response = client->select(request);
    return response;
}

json ViewersTable::getRoomUsers(const size_t id_room) const
{
    json request = {{"SELECT", {"id_user"}},
                    {"FROM", {viewersTableName}},
                    {"WHERE", {"id_room=" + std::to_string(id_room)}}};

    json response = client->select(request);
    return response;
}

json ViewersTable::addUserToRoom(const size_t id_user, const size_t id_room) const
{
    json request = {{"INTO", viewersTableName},
                    {"columns", viewersTableColumns},
                    {"VALUES", {id_user, id_room, 0, GUEST_ROLE}}};

    std::cout << request << std::endl;

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        return getViewersInfo(response["result"]);
    }

    return response;
}

json ViewersTable::getViewersInfo(const size_t id) const
{
    json request = {{"SELECT", {"*"}},
                    {"FROM", {viewersTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);
    return response;
}

json ViewersTable::getUserPointsInRoom(const size_t id_user, const size_t id_room) const
{
    json request = {{"SELECT", {"points"}},
                    {"FROM", {viewersTableName}},
                    {"WHERE", {"id_user=" + std::to_string(id_user), "id_room=" + std::to_string(id_room)}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        response[RESULT_FIELD] = response[RESULT_FIELD][0]["points"];
    }

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
    json request = {{"SELECT", {"role"}},
                    {"FROM", {viewersTableName}},
                    {"WHERE", {"id_user=" + std::to_string(id_user), "id_room=" + std::to_string(id_room)}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        response[RESULT_FIELD] = response[RESULT_FIELD][0]["role"];
    }

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
