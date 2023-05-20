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

    std::shared_ptr<User>  NewUser(User&);

    void GetUserInfo(int);

    bool DeleteUser(int);

    bool UpdateUser(User);

    std::queue<json> queue_request;
    std::queue<json> queue_reply;

private:


};
