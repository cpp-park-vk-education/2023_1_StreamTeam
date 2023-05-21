#include <string>
#include <stdexcept>

#include "room.hpp"

std::string Room::GetName()
{
    return _name;
}

void Room::SetName(std::string name)
{
    _name = name;
}

void Room::setID(int id)
{
    _id = id;
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

bool Room::CreatePlayer (std::shared_ptr<Player> player)
{
    if (player == nullptr)
    {
        return false;
    }
    _player_ptr = player;
    return true;
}

size_t Room::sizeofMembers()
{
    return _members_list.size();
}

User Room::GetMember(size_t i)
{
    if (i >= _members_list.size())
        throw std::invalid_argument("Index out of range");
    return _members_list[i];
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

size_t Room::sizeofMessages()
{
    return _messages_list.size();
}

bool Room::isMessageEmpty()
{
    return _messages_list.empty();
}

Message Room::GetMessage(size_t i)
{
    if (i >= _messages_list.size())
        throw std::invalid_argument("Index out of range");
    return _messages_list[i];
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
