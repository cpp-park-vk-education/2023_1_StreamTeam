#pragma once
#include <string>

class Player
{
public:

    Player();

    Player(int);

    bool PlayVideo();

    bool PlayAudio();

    bool ToggleVideo();

    bool ToggleAudio();

    bool RewindFor();

    bool RewindBack();

    bool ChooseVideo(std::string);

    bool KillVideo();

    ~Player();

private:
    int _leader_id;
};