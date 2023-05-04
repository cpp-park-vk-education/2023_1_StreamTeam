#include <string>

#include "room.hpp"

std::string Room::GetName()
{
    return _name;
}

void Room::SetName(std::string name)
{
    _name = name;
}

std::string Room::GetAvatarUrl()
{
    return _avatar_url;
}

void Room::SetAvatarUrl(std::string url)
{
    _avatar_url = url;
}

int Room::GetLeaderId()
{
    return _leader_id;
}

void Room::SetLeaderId(int id)
{
    _leader_id = id;
}

std::shared_ptr<Player> Room::GetPlayerPtr ()
{
    return _player_ptr;
}

bool Room::CreatePlayer (std::shared_ptr<Player>)
{
    return true;
}

bool Room::AddMember(User user)
{
    if (_members_list.size() == _members_list.max_size() )
    {
        return false;
    }
    else
    {
        _members_list.push_back(user);
        return true;
    }
}

bool Room::DeleteMember(int id)
{
    return true;
}

bool Room::AddMessage(Message message)
{
    if (_messages_list.size() == _messages_list.max_size() )
    {
        return false;
    }
    else
    {
        _messages_list.push_back(message);
        return true;
    }
}

bool Room::DeleteMessage(int id)
{
    return true;
}