#include "UsersTable.hpp"

UsersTable::UsersTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json UsersTable::addUser(const json &info) const
{
    json request = {{"INTO", usersTableName},
                    {"columns", usersTableColumns},
                    {"VALUES", {info["username"], info["email"], info["password"]}}};

    std::cout << request << std::endl;

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        return getUserInfo(response["result"]);
    }

    return response;
}

json UsersTable::deleteUser(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->remove(request);
    return response;
}

json UsersTable::updateUser(const json &info) const
{
    json request = info;
    json response = client->update(request);
    return response;
}

bool UsersTable::checkUserByID(const size_t id) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {usersTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == ERROR_STATUS)
    {
        return false;
    }
    return true;
}

bool UsersTable::checkUserByEmail(const std::string &email) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {usersTableName}},
                    {"WHERE", {"email='" + email + "'"}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == ERROR_STATUS)
    {
        return false;
    }
    return true;
}

bool UsersTable::checkUserByUsername(const std::string &username) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {usersTableName}},
                    {"WHERE", {"username='" + username + "'"}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == ERROR_STATUS)
    {
        return false;
    }
    return true;
}

json UsersTable::getUserInfo(const size_t id) const
{
    json request = {{"SELECT", {"*"}},
                    {"FROM", {usersTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);
    return response;
}

json UsersTable::getUserIdByEmail(const std::string &email) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {usersTableName}},
                    {"WHERE", {"email='" + email + "'"}}};

    json response = client->select(request);
    return response;
}

json UsersTable::getUserIdByUsername(const std::string &username) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {usersTableName}},
                    {"WHERE", {"username='" + username + "'"}}};

    json response = client->select(request);
    return response;
}

json UsersTable::getUserPassword(const size_t id) const
{
    json request = {{"SELECT", {"password"}},
                    {"FROM", {usersTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);
    return response;
}
