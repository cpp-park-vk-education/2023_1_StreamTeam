#pragma once
#include <string>
#include <memory>
#include <vector>

#include "player.hpp"
#include "user.hpp"
#include "message.hpp"

class Room 
{
public:
    int getID();

    std::string GetName();

    void SetName(std::string);

    int GetLeaderId();

    void SetLeaderId(int);

    std::shared_ptr<Player> GetPlayerPtr ();

    bool CreatePlayer (std::shared_ptr<Player>);

    size_t sizeofMembers();

    User GetMember(size_t);

    bool AddMember(User);

    bool DeleteMember(int);

    size_t sizeofMessages();

    bool isMessageEmpty();

    Message GetMessage(size_t);

    bool AddMessage(Message);

    bool DeleteMessage(int);

private:
    int _id;
    std::string _name;
    int _leader_id;
    std::shared_ptr<Player> _player_ptr;

    std::vector<User> _members_list;
    std::vector<Message> _messages_list;
};
