cmake_minimum_required(VERSION 3.10)
project(StreamingServer)

set(CMAKE_CXX_STANDARD 17)

set(STREAMING_SERVER_SRC_FILES src/video_info.cpp)
set(STREAMING_SERVER_INC_FILES include/video_info.hpp)

find_package(Boost 1.82.0 REQUIRED COMPONENTS filesystem)
include_directories(boost_test ${Boost_INCLUDE_DIRS})
find_package(Threads REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_library(StreamingServer ${STREAMING_SERVER_SRC_FILES} ${STREAMING_SERVER_INC_FILES})
target_link_libraries(StreamingServer ${Boost_LIBRARIES})
target_include_directories(StreamingServer PUBLIC include)
