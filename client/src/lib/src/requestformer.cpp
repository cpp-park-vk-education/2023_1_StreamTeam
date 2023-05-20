#include <stdlib.h>

#include "requestformer.hpp"
#include "user.hpp"
#include "room.hpp"
#include "message.hpp"

std::shared_ptr<User> RequestFormer::Authenticate(User &auth_user)
{
    json auth_req = {
            "request",
            {
                {"method", "auth"},
                {"data", {
                    {"email", auth_user.GetEmail()},
                    {"password", auth_user.GetPassword()}
                }}
            }
        };

    queue_request.push(auth_req);

    // Wait for answer for 5 sec
    for (int waiting = 0; waiting < 5; ++waiting)
    {
        sleep(1);
        if (!queue_reply.empty())
        {
            json reply = queue_reply.front();
            queue_reply.pop();

            if (!(reply["status"] == "ok"))
                return nullptr;

            std::shared_ptr<User> user (new User);
            user->SetId(reply["data"][0]["id"]);
            user->SetName(reply["data"][0]["name"]);
            user->SetEmail(auth_user.GetEmail());
            user->SetPassword(auth_user.GetPassword());
            return user;
        }
    }

    return nullptr;
}

std::shared_ptr<User> RequestFormer::NewUser(User& new_user)
{
    json new_auth_req = {
            "request",
            {
                {"method", "new"},
                {"data", {
                    {"name", new_user.GetName()},
                    {"email", new_user.GetEmail()},
                    {"password", new_user.GetPassword()}
                }}
            }
        };

    queue_request.push(new_auth_req);

    // Wait for answer for 5 sec
    for (int waiting = 0; waiting < 5; ++waiting)
    {
        sleep(1);
        if (!queue_reply.empty())
        {
            json reply = queue_reply.front();
            queue_reply.pop();

            if (!(reply["status"] == "ok"))
                return nullptr;

            std::shared_ptr<User> user (new User);
            user->SetId(reply["data"][0]["id"]);
            user->SetName(reply["data"][0]["name"]);
            user->SetEmail(new_user.GetEmail());
            user->SetPassword(new_user.GetPassword());
            return user;
        }
    }
    return nullptr;
}


void RequestFormer::GetUserInfo(int)
{

}


bool RequestFormer::DeleteUser(int)
{
    return true;
}
