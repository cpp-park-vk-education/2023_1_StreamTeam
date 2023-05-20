#pragma once

#include <vector>
#include <string>

#include "nlohmann/json.hpp"
#include "session.hpp"
#include "UsersTable.hpp"


using json = nlohmann::json;
using session_ptr = std::shared_ptr<Session>;
using db_ptr = std::shared_ptr<IDatabase>;

class Auth {
    UsersTable table_;
    const std::vector<std::string> required_fields{"method", "data"};
    const std::vector<std::string> allowed_methods{"auth", "create"};
    const std::vector<std::string> required_to_register{"username", "email",
                                                          "password"};
    const std::vector<std::string> required_to_check{"type", "name", "password"};

   public:
    Auth(const json& request, db_ptr database, session_ptr session);

   private:
    void CheckUser(const json& request, session_ptr session);

    void CreateUser(const json& request, session_ptr session);
};
