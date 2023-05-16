#include "../include/video_stream.hpp"

VideoStream::VideoStream(): _codec_name(DEFAULT_CODEC) {}

std::shared_ptr<AudioEncoder> VideoStream::getAudioEncoder() {
    return _audio_encoder;
}

std::shared_ptr<VideoEncoder> VideoStream::getVideoEncoder() {
    return _video_encoder;
}

void VideoStream::open(const std::string& filename) {
    _video_encoder = std::make_shared<VideoEncoder>(1920, 1080, 30, 10000000);
}

void VideoStream::setCodec(const std::string& codecName) {}

void VideoStream::start(const std::string& host, int port) {}

void VideoStream::stop() {}

std::string VideoStream::getCodecName() {
    return _codec_name;
}
