#include <stdexcept>
#include "../include/video_info.hpp"


VideoInfo::VideoInfo(const std::string& file_path)
        : file_path_(file_path)
{
    if (!openFile()) {
        std::cout << "FILENAME:" << file_path;

        throw std::runtime_error("Failed to open file '" + file_path + "' from VideoInfo");
    }
    if (!findStreamInfo()) {
        throw std::runtime_error("Failed to find stream information from VideoInfo");
    }
}

VideoInfo::~VideoInfo() {
    if (video_stream_) {
        avcodec_close(video_stream_->codec);
        avcodec_free_context(&video_stream_->codec);
    }
    if (audio_stream_) {
        avcodec_close(audio_stream_->codec);
        avcodec_free_context(&audio_stream_->codec);
    }
    if (format_context_) {
        avformat_close_input(&format_context_);
    }
}

VideoParams VideoInfo::getVideoInfo() {
    VideoParams video_params;
    if (video_stream_) {
        video_params.width = video_stream_->codec->width;
        video_params.height = video_stream_->codec->height;
        video_params.fps = av_q2d(video_stream_->avg_frame_rate);
        video_params.bitrate = video_stream_->codec->bit_rate;
    }
    return video_params;
}

AudioParams VideoInfo::getAudioInfo() {
    AudioParams audio_params;
    if (audio_stream_) {
        audio_params.channels = audio_stream_->codecpar->channels;
        audio_params.sample_rate = audio_stream_->codecpar->sample_rate;
        audio_params.bitrate = audio_stream_->codec->bit_rate;
    }
    return audio_params;
}

int VideoInfo::getDuration() {
    return format_context_->duration / AV_TIME_BASE;
}

bool VideoInfo::openFile() {
    int ret = avformat_open_input(&format_context_, file_path_.c_str(), nullptr, nullptr);
    if (ret < 0) {
        return false;
    }
    ret = avformat_find_stream_info(format_context_, nullptr);
    return ret < 0 ? false : true;
}

bool VideoInfo::findStreamInfo() {
    for (unsigned int i = 0; i < format_context_->nb_streams; i++) {
        if (format_context_->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            video_stream_index_ = i;
            video_stream_ = format_context_->streams[i];
            AVCodec* codec = avcodec_find_decoder(video_stream_->codecpar->codec_id);
            if (!codec) {
                return false;
            }
            AVCodecContext* codec_ctx = avcodec_alloc_context3(codec);
            if (!codec_ctx) {
                return false;
            }
            if (avcodec_parameters_to_context(codec_ctx, video_stream_->codecpar) < 0) {
                return false;
            }
            if (avcodec_open2(codec_ctx, codec, nullptr) < 0) {
                return false;
            }
            video_stream_->codec = codec_ctx;
        } else if (format_context_->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            audio_stream_index_ = i;
            audio_stream_ = format_context_->streams[i];
            AVCodec* codec = avcodec_find_decoder(audio_stream_->codecpar->codec_id);
            if (!codec) {
                return false;
            }
            AVCodecContext* codec_ctx = avcodec_alloc_context3(codec);
            if (!codec_ctx) {
                return false;
            }
            if (avcodec_parameters_to_context(codec_ctx, audio_stream_->codecpar) < 0) {
                return false;
            }
            if (avcodec_open2(codec_ctx, codec, nullptr) < 0) {
                return false;
            }
            audio_stream_->codec = codec_ctx;
        }
    }
    if (video_stream_index_ == -1 && audio_stream_index_ == -1) {
        return false;
    }
    return true;
}
