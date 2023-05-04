#include <string>
#include <memory>

#include "user.hpp"


int User::GetId ()
{
    return _id;
}

std::string User::GetName()
{
    return _name;
}

std::string User::GetAvatarUrl()
{
    return _avatar_url;
}

std::shared_ptr<Player> User::GetActivePlayer()
{
    return _active_player;
}

void User::SetId (int id)
{
    _id = id;
}

void User::SetName(std::string name) 
{
    _name = name;
}

void User::SetAvatarUrl(std::string url)
{
    _avatar_url = url;
}

void User::SetActivePlayer(std::shared_ptr<Player> ptr) 
{
    _active_player = ptr;
}