#pragma once

#include "video_encoder.hpp"
#include "audio_encoder.hpp"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>
#include <memory>

extern "C" {
    #include <libavutil/avutil.h>
    #include <libavutil/opt.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}

class VideoStream {
public:
    const std::string DEFAULT_CODEC = "H264";

    VideoStream();
    void open(const std::string& filename);
    void setCodec(const std::string& codecName);

    void start(const std::string& host, int port);
    void stop();
    std::string getCodecName();

    std::shared_ptr<VideoEncoder> getVideoEncoder();
    std::shared_ptr<AudioEncoder> getAudioEncoder();
private:
    std::shared_ptr<AudioEncoder> _audio_encoder;
    std::shared_ptr<VideoEncoder> _video_encoder;

    void sendPacket(AVPacket* pkt);
    void cleanup();

    AVCodecContext* _codec_context;
    AVFormatContext* _format_context;
    AVStream* _stream;
    AVFrame* _frame;
    AVPacket* _pkt;
    std::string _codec_name;

    bool running;
};
