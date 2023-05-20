#pragma once
#include <string>
#include <memory>
#include "user.hpp"
#include "room.hpp"
#include "message.hpp"

#include "../../../include/json.hpp"
#include <memory>
#include <queue>

using json = nlohmann::json;

class RequestFormer
{
public:

    std::shared_ptr<User> Authenticate(User&);

    void GetUserInfo(int);

    bool NewUser(User&);

    bool DeleteUser(int);

    bool UpdateUser(User);

    std::unique_ptr<json> request_ptr;
    std::unique_ptr<json> reply_ptr;

private:


};
