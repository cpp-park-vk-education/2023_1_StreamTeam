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

    *request_ptr = auth_req;

    // Wait for answer for 5 sec
    for (int waiting = 0; waiting < 5; ++waiting)
    {
        sleep(1);
        if (reply_ptr)
        {
            json reply = *reply_ptr;
            reply_ptr.reset();

            if (!(reply["status"] == "ok"))
                return nullptr;

            std::shared_ptr<User> user (new User);
            user->SetName(auth_user.GetName());
            user->SetEmail(auth_user.GetEmail());
            user->SetPassword(auth_user.GetPassword());
            user->SetId(3);
            return user;
        }
    }

    return nullptr;
}

void RequestFormer::GetUserInfo(int)
{

}

bool RequestFormer::NewUser(User& new_user)
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

    *request_ptr = new_auth_req;

    // Wait for answer for 5 sec
    for (int wait = 0; wait < 5; ++wait)
    {
        sleep(1);
        if (reply_ptr)
        {
            json reply = *reply_ptr;
            reply_ptr.reset();

            if (reply["status"] == "ok")
                return true;
            return false;
        }
    }

    return false;
}

bool RequestFormer::DeleteUser(int)
{
    return true;
}
