#include "RoomsTable.hpp"

#include <iostream>

RoomsTable::RoomsTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json RoomsTable::addRoom(const json &info) const
{
    json request = info;
    json response = client->insert(request);
    return response;
}

json RoomsTable::deleteRoom(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->remove(request);
    return response;
}

json RoomsTable::updateRoom(const json &info) const
{
    json request = info;
    json response = client->update(request);
    return response;
}

bool RoomsTable::checkRoom(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);
    return true;
}

json RoomsTable::getRoomInfo(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);
    return response;
}

json RoomsTable::getAllRooms() const
{
    json request = {{"id", "*"}};
    json response = client->select(request);
    return response;
}

json RoomsTable::getCurrentFilm(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);
    return response;
}

bool RoomsTable::checkCurrentFilm(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);
    return true;
}
