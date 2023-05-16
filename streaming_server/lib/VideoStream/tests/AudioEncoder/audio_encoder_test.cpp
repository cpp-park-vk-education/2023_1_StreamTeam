#include "gtest/gtest.h"
#include "audio_encoder.hpp"

class AudioEncoderTest : public ::testing::Test {
protected:
    int test_frequency = 40000000;
    int test_canals = 4;
    int test_bit_depth = 1000000;
    std::string test_codec = "MP3";


    AudioEncoder audio_encoder{test_frequency, test_canals, test_bit_depth, test_codec};
};

TEST_F(AudioEncoderTest, TestEncode) {
    std::vector<uint8_t> data(100);
        for (int i = 0; i < data.size(); ++i) {
        data[i] = static_cast<uint8_t>(i % 256);
    }

    std::vector<uint8_t> encoded_data = audio_encoder.encode(data.data());

    ASSERT_FALSE(encoded_data.empty());
}

TEST_F(AudioEncoderTest, EncodeNullptr) {
    std::vector<uint8_t> encoded_data = audio_encoder.encode(nullptr);

    EXPECT_EQ(encoded_data.size(), 0);
}
