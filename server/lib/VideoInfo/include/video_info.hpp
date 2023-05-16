#pragma once

#include <iostream>
#include <string>
#include <vector>

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavutil/imgutils.h>
    #include <libavutil/opt.h>
    #include <libavutil/samplefmt.h>
    #include <libavutil/time.h>
    #include <libswscale/swscale.h>
    #include <libavformat/avformat.h>
}

struct VideoParams {
    int width = 0;
    int height = 0;
    int fps = 0;
    int bitrate = 0;
};

struct AudioParams {
    int channels = 0;
    int sample_rate = 0;
    int bitrate = 0;
};

class VideoInfo {
public:
    explicit VideoInfo(const std::string& file_path);
    ~VideoInfo();

    VideoParams getVideoInfo();
    AudioParams getAudioInfo();
    int getDuration();

private:
    bool openFile();
    bool findStreamInfo();

    std::string file_path_;
    AVFormatContext* format_context_ = nullptr;
    int video_stream_index_ = -1;
    AVStream* video_stream_ = nullptr;
    int audio_stream_index_ = -1;
    AVStream* audio_stream_ = nullptr;
};
