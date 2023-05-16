#pragma once

#include "encoder.hpp"

class VideoEncoder : IEncoder {
public:
    VideoEncoder() = delete;
    VideoEncoder(int width, int height, int fps, int bitrate);
    ~VideoEncoder() override;

    std::vector<uint8_t> encode(const uint8_t* data) override;

    void setWidth(int width);
    void setHeight(int height);
    void setFps(int fps);
    void setBitrate(int bitrate);

    int getFps();
    int getBitrate();
    int getHeight();
    int getWidth();
private:
    int _width;
    int _height;
    int _fps;
    int _bitrate;
};
