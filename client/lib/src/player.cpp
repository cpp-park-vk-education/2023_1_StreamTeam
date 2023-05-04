#include <string>

#include "player.hpp"


Player::Player() {}

Player::Player(int id)
{
    _leader_id = id;
}

bool Player::PlayVideo()
{
    return true;
}

bool Player::PlayAudio()
{
    return true;
}

bool Player::ToggleVideo()
{
    return true;
}

bool Player::ToggleAudio()
{
    return true;
}

bool Player::RewindFor()
{
    return true;
}

bool Player::RewindBack()
{
    return true;
}

bool Player::ChooseVideo(std::string)
{
    return true;
}

bool Player::KillVideo()
{
    return true;
}

Player::~Player() {}