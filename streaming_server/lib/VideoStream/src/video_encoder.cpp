#include "../include/video_encoder.hpp"

std::vector<uint8_t> VideoEncoder::encode(const uint8_t* data) {
    std::vector<uint8_t> x;
    return x;
}

VideoEncoder::VideoEncoder(int width, int height, int fps, int bitrate)
    : _width(width), _height(height), _fps(fps), _bitrate(bitrate) {}

VideoEncoder::~VideoEncoder() noexcept {}

void VideoEncoder::setWidth(int width) {
    _width = width;
}
int VideoEncoder::getWidth() {
    return _width;
}

void VideoEncoder::setHeight(int height) {
    _height = height;
}
int VideoEncoder::getHeight() {
    return _height;
}

void VideoEncoder::setBitrate(int bitrate) {
    _bitrate = bitrate;
}
int VideoEncoder::getBitrate() {
    return _bitrate;
}

void VideoEncoder::setFps(int fps) {
    _fps = fps;
}
int VideoEncoder::getFps() {
    return _fps;
}
