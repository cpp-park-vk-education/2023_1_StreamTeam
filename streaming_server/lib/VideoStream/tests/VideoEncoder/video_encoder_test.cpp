#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include "video_encoder.hpp"

class VideoEncoderTest : public ::testing::Test {
protected:
    const int test_width = 1920;
    const int test_height = 1080;
    const int test_fps = 30;
    const int test_bitrate = 1000000;

    VideoEncoder video_encoder{test_width, test_height, test_fps, test_bitrate};
};

TEST_F(VideoEncoderTest, Encode) {
    std::vector<uint8_t> data(test_width * test_height);
    for (int i = 0; i < data.size(); ++i) {
        data[i] = static_cast<uint8_t>(i % 256);
    }

    std::vector<uint8_t> encoded_data = video_encoder.encode(data.data());

    ASSERT_FALSE(encoded_data.empty());
}

TEST_F(VideoEncoderTest, EncodeNullptr) {
    std::vector<uint8_t> encoded_data = video_encoder.encode(nullptr);

    EXPECT_EQ(encoded_data.size(), 0);
}

TEST_F(VideoEncoderTest, EncodeNegativeDimensions) {
    EXPECT_THROW(VideoEncoder(-1, -1, -1, -1), std::invalid_argument);
}

TEST_F(VideoEncoderTest, GetWidth) {
    EXPECT_EQ(video_encoder.getWidth(), test_width);
}

TEST_F(VideoEncoderTest, GetHeight) {
    EXPECT_EQ(video_encoder.getHeight(), test_height);
}

TEST_F(VideoEncoderTest, GetBitrate) {
    EXPECT_EQ(video_encoder.getBitrate(), test_bitrate);
}

TEST_F(VideoEncoderTest, GetFps) {
    EXPECT_EQ(video_encoder.getFps(), test_fps);
}

TEST_F(VideoEncoderTest, SetWidth) {
    video_encoder.setWidth(123);
    EXPECT_EQ(video_encoder.getWidth(), 123);
}

TEST_F(VideoEncoderTest, SetHeight) {
    video_encoder.setHeight(1235);
    EXPECT_EQ(video_encoder.getHeight(), 1235);
}

TEST_F(VideoEncoderTest, SetBitrate) {
    video_encoder.setBitrate(1234);
    EXPECT_EQ(video_encoder.getBitrate(), 1234);
}

TEST_F(VideoEncoderTest, SetFps) {
    video_encoder.setFps(1231);
    EXPECT_EQ(video_encoder.getFps(), 1231);
}
