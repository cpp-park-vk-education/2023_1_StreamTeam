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
    bool _video_is_active;
    bool _audio_is_active;
};