#pragma once
#include <string>
#include <memory>

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

    bool SetActivePlayer(std::shared_ptr<Player>);

private:
    int _id;
    std::string _name;
    std::string _avatar_url;
    std::shared_ptr<Player> _active_player = nullptr;
    
};