#pragma once

#include "encoder.hpp"

class AudioEncoder : IEncoder {
public:
    AudioEncoder();
    ~AudioEncoder();

    std::vector<uint8_t> encode(const uint8_t* data) override;
};
