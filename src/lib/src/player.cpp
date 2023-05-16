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
    if (!_video_is_active)
    {
        return false;
    }
    return true;
}

bool Player::ToggleAudio()
{
    if (!_video_is_active)
    {
        return false;
    }
    return true;
}

bool Player::RewindFor()
{
    if (!_video_is_active)
    {
        return false;
    }
    return true;
}

bool Player::RewindBack()
{
    if (!_video_is_active)
    {
        return false;
    }
    return true;
}

bool Player::ChooseVideo(std::string video)
{
    if (video == "") 
    {
        return false;
    }
    _video_is_active = 1;
    return true;
}

bool Player::KillVideo()
{
    _video_is_active = 0;
    return true;
}

Player::~Player() {}