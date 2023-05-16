#pragma once

#include "encoder.hpp"
#include <string>

class AudioEncoder : IEncoder {
public:
    AudioEncoder() = delete;
    AudioEncoder(int frequency, int canals, int bit_depth, std::string& codec_name);
    ~AudioEncoder() override;

    std::vector<uint8_t> encode(const uint8_t* data) override;

    void setFrequency(int freq) {
        _frequency = freq;
    }

    void setCanals(int canals){
        _canals = canals;
    }

    void setBitDepth(int bit_depth) {
        _bit_depth = bit_depth;
    }

    void setCodecName(std::string& codec_name) {
        _codec_name = codec_name;
    }

    int getFrequency() {
        return _frequency;
    }

    int getCanals() {
        return _canals;
    }

    int getBitDepth() {
        return _bit_depth;
    }

    std::string getCodecName() {
        return _codec_name;
    }

private:
    int _frequency;
    int _canals;
    int _bit_depth;
    std::string _codec_name;
};
