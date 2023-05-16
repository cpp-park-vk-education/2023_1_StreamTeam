cmake_minimum_required(VERSION 3.10)
project(VideoStream)

set(CMAKE_CXX_STANDARD 17)

set(VIDEO_STREAM_SRC_FILES
        src/audio_encoder.cpp
        src/video_encoder.cpp
        src/video_stream.cpp
        )

set(VIDEO_STREAM_INC_FILES
        include/audio_encoder.hpp
        include/encoder.hpp
        include/video_encoder.hpp
        include/video_stream.hpp
        )

add_library(VideoStream ${VIDEO_STREAM_SRC_FILES} ${VIDEO_STREAM_INC_FILES})
target_include_directories(VideoStream PUBLIC include)

add_subdirectory(tests)
