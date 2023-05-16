#include <gtest/gtest.h>
#include "video_stream.hpp"

class VideoStreamTest : public ::testing::Test {
protected:
    const std::string test_filename = "test.mp4";
    const std::string test_wrong_filename = "nonexistent.mp4";
    const std::string test_codec = "H264";
    const int video_width = 1920;
    const int video_height = 1080;
    const int video_fps = 30;
    const int video_bitrate = 10000000;

    VideoStream stream;
};

TEST_F(VideoStreamTest, GetCodecName) {
    EXPECT_EQ(stream.getCodecName(), test_codec);
}

TEST_F(VideoStreamTest, SetCodec) {
    stream.setCodec("hellowrold");
    EXPECT_EQ(stream.getCodecName(), "hellowrold");
}

TEST_F(VideoStreamTest, GetVideoEncoder) {
    EXPECT_EQ(stream.getVideoEncoder(), nullptr);
}

TEST_F(VideoStreamTest, OpenFile) {
    EXPECT_NO_THROW(stream.open(test_filename));
}

TEST_F(VideoStreamTest, OpenFileNotFound) {
    EXPECT_THROW(stream.open(test_wrong_filename), std::runtime_error);
}

TEST_F(VideoStreamTest, OpenFileSetEncoderProperties) {
    stream.open(test_filename);
    auto encoder = stream.getVideoEncoder();

    EXPECT_NE(encoder, nullptr);

    EXPECT_EQ(encoder->getWidth(), video_width);
    EXPECT_EQ(encoder->getHeight(), video_height);
    EXPECT_EQ(encoder->getBitrate(), video_bitrate);
    EXPECT_EQ(encoder->getFps(), video_fps);
}
