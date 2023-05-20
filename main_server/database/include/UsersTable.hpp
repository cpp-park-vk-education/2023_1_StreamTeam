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
    bool checkUserByID(const size_t id) const;
    bool checkUserByEmail(const std::string &email) const;
    bool checkUserByUsername(const std::string &username) const;
    json getUserInfo(const size_t id) const;
    json getUserIdByEmail(const std::string &email) const;
    json getUserIdByUsername(const std::string &username) const;
    json getUserPassword(const size_t id) const;

private:
    std::shared_ptr<IDatabase> client;
};
