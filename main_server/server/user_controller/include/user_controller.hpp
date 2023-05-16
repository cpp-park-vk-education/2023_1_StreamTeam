#pragma once

#include <array>
#include <string>

#include "UsersTable.hpp"
#include "nlohmann/json.hpp"
#include "session.hpp"

using json = nlohmann::json;
using db_ptr = std::shared_ptr<IDatabase>;
using session_ptr = std::shared_ptr<Session>;

class UserController {
    const std::array<std::string, 3> allowed_methods_{
        "deleteUser", "updateUser", "getUserInfo"};
    UsersTable table_;

   public:
    UserController(const json& request, db_ptr database, session_ptr session);

   private:
    void UpdateUser(const json& data, session_ptr session);
    void DeleteUser(session_ptr session);
    void GetUserInfo(const json& data, session_ptr session);
};