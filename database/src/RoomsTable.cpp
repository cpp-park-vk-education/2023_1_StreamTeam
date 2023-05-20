#include "RoomsTable.hpp"

#include <iostream>

RoomsTable::RoomsTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json RoomsTable::addRoom(const json &info) const
{
    json request = {{"INTO", roomsTableName},
                    {"columns", roomsTableColumns},
                    {"VALUES", {info["name"], info["creator"], info["current_film"]}}};

    std::cout << request << std::endl;

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        return getRoomInfo(response[RESULT_FIELD]);
    }

    return response;
}

json RoomsTable::deleteRoom(const size_t id) const
{
    if (!checkRoom(id))
    {
        return {{STATUS_FIELD, ERROR_STATUS},
                {"msg", "A room with such ID does not exist."}};
    }
    json request = {{"FROM", roomsTableName},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->remove(request);

    return response;
}

json RoomsTable::updateRoom(const json &info) const
{
    size_t id = info["id"];
    if (!checkRoom(id))
    {
        return {{STATUS_FIELD, ERROR_STATUS},
                {"msg", "A room with such ID does not exist."}};
    }
    json request = {{"table", roomsTableName},
                    {"SET", info["data"]},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->update(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        return getRoomInfo(id);
    }

    return response;
}

bool RoomsTable::checkRoom(const size_t id) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {roomsTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == ERROR_STATUS)
    {
        return false;
    }
    return true;
}

json RoomsTable::getRoomInfo(const size_t id) const
{
    json request = {{"SELECT", {"*"}},
                    {"FROM", {roomsTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);

    return response;
}

json RoomsTable::getAllRooms() const
{
    json request = {{"SELECT", {"*"}},
                    {"FROM", {roomsTableName}}};

    json response = client->select(request);

    return response;
}

json RoomsTable::getCurrentFilm(const size_t id) const
{
    json request = {{"SELECT", {"current_film"}},
                    {"FROM", {roomsTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);

    return response;
}

json RoomsTable::checkCurrentFilm(const size_t id) const
{
    json request = {{"SELECT", {"current_film"}},
                    {"FROM", {roomsTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        response[RESULT_FIELD] = !response[RESULT_FIELD][0]["current_film"].is_null();
    }

    return response;
}
