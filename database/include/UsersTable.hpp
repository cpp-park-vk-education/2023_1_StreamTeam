#pragma once

#include "PostgreSQL.hpp"

class UsersTable
{
public:
    UsersTable() = default;
    UsersTable(std::shared_ptr<IDatabase> client);

    json addUser(const json &info) const;
    json deleteUser(const size_t id) const;
    json updateUser(const json &info) const;
    bool checkUser(const size_t id) const;
    json getUserInfo(const size_t id) const;

private:
    std::shared_ptr<IDatabase> client;
};
