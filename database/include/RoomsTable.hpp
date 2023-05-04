#pragma once

#include "PostgreSQL.hpp"

class RoomsTable
{
public:
    RoomsTable() = default;
    RoomsTable(std::shared_ptr<IDatabase> client);

    json addRoom(const json &info) const;
    json deleteRoom(const size_t id) const;
    json updateRoom(const json &info) const;
    bool checkRoom(const size_t id) const;
    json getRoomInfo(const size_t id) const;
    json getAllRooms() const;

private:
    std::shared_ptr<IDatabase> client;
};
