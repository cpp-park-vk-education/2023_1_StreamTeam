#pragma once

#include <vector>
#include <cstdint>

class IEncoder {
public:
    virtual ~IEncoder() = default;
    virtual std::vector<uint8_t> encode(const uint8_t* data) = 0;
};
