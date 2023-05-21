#include <gtest/gtest.h>

// Include the header file for VideoInfo
#include "video_info.hpp"

// Test fixture for VideoInfo
class VideoInfoTest : public testing::Test {
protected:
    // Member variables
    std::string file_path;
    VideoInfo* video_info;

    // SetUp function will be called before each test case
    void SetUp() override {
        // Set up the file path
        file_path = "/media/sf_CLionProjects/2023_1_StreamTeam/server/static/input.mp4";

        // Create a new VideoInfo object
        video_info = new VideoInfo(file_path);
    }

    // TearDown function will be called after each test case
    void TearDown() override {
        // Delete the VideoInfo object
        delete video_info;
    }
};

// Test case for getVideoInfo() method
TEST_F(VideoInfoTest, GetVideoInfo) {
    // Call the getVideoInfo() method
    VideoParams video_params = video_info->getVideoInfo();

    // Check the expected values
    EXPECT_EQ(video_params.width, 1280);
    EXPECT_EQ(video_params.height, 720);
    EXPECT_EQ(video_params.fps, 30);
    EXPECT_EQ(video_params.bitrate, 165471);
}

// Test case for getAudioInfo() method
TEST_F(VideoInfoTest, GetAudioInfo) {
    // Call the getAudioInfo() method
    AudioParams audio_params = video_info->getAudioInfo();

    // Check the expected values
    EXPECT_EQ(audio_params.channels, 2);
    EXPECT_EQ(audio_params.sample_rate, 44100);
    EXPECT_EQ(audio_params.bitrate, 2067);
}

// Test case for getDuration() method
// Test case for getDuration() method
TEST_F(VideoInfoTest, GetDuration) {
    // Call the getDuration() method
    int duration = video_info->getDuration();

    // Check the expected value
    EXPECT_EQ(duration, 4);
}

TEST_F(VideoInfoTest, throwsExceptionIfFileNotFound) {
    EXPECT_THROW(VideoInfo("nonexistent_file.mp4"), std::runtime_error);
}

// Run the tests
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}