cmake_minimum_required(VERSION 3.10)
project(VideoInfo)

set(CMAKE_CXX_STANDARD 17)

set(VIDEO_INFO_SRC_FILES src/video_info.cpp)
set(VIDEO_INFO_INC_FILES include/video_info.hpp)

set(FFMPEG_LIBRARIES "/usr/lib/x86_64-linux-gnu/libavcodec.so;/usr/lib/x86_64-linux-gnu/libavformat.so;/usr/lib/x86_64-linux-gnu/libavutil.so;/usr/lib/x86_64-linux-gnu/libswscale.so")

add_library(VideoInfo ${VIDEO_INFO_SRC_FILES} ${VIDEO_INFO_INC_FILES})
target_link_libraries(VideoInfo ${FFMPEG_LIBRARIES})
target_include_directories(VideoInfo PUBLIC include)

add_subdirectory(tests)
