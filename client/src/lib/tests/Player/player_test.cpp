#include "gtest/gtest.h"
#include <memory>
#include "message.hpp"

class PlayerTest : public ::testing::Test {
protected:
    Player player;
};

TEST_F(PlayerTest, TestPlayVideo) {
    bool flag = player.PlayVideo();
    EXPECT_EQ(flag, true);
}

TEST_F(PlayerTest, TestPlayAudio) {
    bool flag = player.PlayAudio();
    EXPECT_EQ(flag, true);
}

TEST_F(PlayerTest, TestToggleVideoWhenActive) {
    player.ChooseVideo("vid");
    bool flag = player.ToggleVideo();
    EXPECT_EQ(flag, true);
}

TEST_F(PlayerTest, TestToggleVideoWhenInactive) {
    player.KillVideo();
    bool flag = player.ToggleVideo();
    EXPECT_EQ(flag, false);
}

TEST_F(PlayerTest, TestToggleAudioWhenActive) {
    player.ChooseVideo("vid");
    bool flag = player.ToggleAudio();
    EXPECT_EQ(flag, true);
}

TEST_F(PlayerTest, TestToggleAudioWhenInactive) {
    player.KillVideo();
    bool flag = player.ToggleAudio();
    EXPECT_EQ(flag, false);
}

TEST_F(PlayerTest, TestRewindForWhenActive) {
    player.ChooseVideo("vid");
    bool flag = player.RewindFor();
    EXPECT_EQ(flag, true);
}

TEST_F(PlayerTest, TestRewindForWhenInactive) {
    player.KillVideo();
    bool flag = player.RewindFor();
    EXPECT_EQ(flag, false);
}

TEST_F(PlayerTest, TestRewindBackWhenActive) {
    player.ChooseVideo("vid");
    bool flag = player.RewindBack();
    EXPECT_EQ(flag, true);
}

TEST_F(PlayerTest, TestRewindBackWhenInactive) {
    player.KillVideo();
    bool flag = player.RewindBack();
    EXPECT_EQ(flag, false);
}

TEST_F(PlayerTest, TestChooseVid) {
    bool flag = player.ChooseVideo("vid");
    EXPECT_EQ(flag, true);
}

TEST_F(PlayerTest, TestChooseVidNull) {
    bool flag = player.ChooseVideo("");
    EXPECT_EQ(flag, false);
}
