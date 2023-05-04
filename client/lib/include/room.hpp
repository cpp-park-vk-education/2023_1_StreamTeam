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

    std::string GetName();

    void SetName(std::string);

    std::string GetAvatarUrl();

    void SetAvatarUrl(std::string);

    int GetLeaderId();

    void SetLeaderId(int);

    std::shared_ptr<Player> GetPlayerPtr ();

    bool CreatePlayer (std::shared_ptr<Player>);

    bool AddMember(User);

    bool DeleteMember(int);

    bool AddMessage(Message);

    bool DeleteMessage(int);

private:
    std::string _name;
    std::string _avatar_url;
    int _leader_id;
    std::shared_ptr<Player> _player_ptr;

    std::vector<User> _members_list;
    std::vector<Message> _messages_list;

};
