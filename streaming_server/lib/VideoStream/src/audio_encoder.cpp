#include "../include/audio_encoder.hpp"

AudioEncoder::AudioEncoder(int frequency, int canals, int bit_depth, std::string& codec_name)
: _frequency(frequency), _canals(canals), _bit_depth(bit_depth), _codec_name(std::move(codec_name)) {}

std::vector<uint8_t> AudioEncoder::encode(const uint8_t* data) {
    std::vector<uint8_t> x;
    return x;
}

AudioEncoder::~AudioEncoder() noexcept {}
