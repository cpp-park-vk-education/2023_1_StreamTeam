#pragma once
#include <string>

#include "player.hpp"

class User
{
public:
    int GetId ();

    std::string GetName();

    std::string GetAvatarUrl();

    std::shared_ptr<Player> GetActivePlayer();

    void SetId (int);

    void SetName(std::string);

    void SetAvatarUrl(std::string);

    void SetActivePlayer(std::shared_ptr<Player>);

private:
    int _id;
    std::string _name;
    std::string _avatar_url;
    std::shared_ptr<Player> _active_player = nullptr;
    
};