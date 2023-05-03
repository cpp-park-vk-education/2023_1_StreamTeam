cmake_minimum_required(VERSION 3.10)

project(server)

set(CMAKE_CXX_STANDARD 20)

# Locate necessary packages
find_package(PostgreSQL REQUIRED)

find_path(AVCODEC_INCLUDE_DIR libavcodec/avcodec.h)
find_library(AVCODEC_LIBRARY avcodec)

find_path(AVFORMAT_INCLUDE_DIR libavformat/avformat.h)
find_library(AVFORMAT_LIBRARY avformat)

find_path(AVUTIL_INCLUDE_DIR libavutil/avutil.h)
find_library(AVUTIL_LIBRARY avutil)

find_path(AVDEVICE_INCLUDE_DIR libavdevice/avdevice.h)
find_library(AVDEVICE_LIBRARY avdevice)

find_package(GTest REQUIRED)
# Set include directories
include_directories(${PostgreSQL_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/VideoStream/include)
include_directories(${GTEST_INCLUDE_DIRS})

# Add subdirectories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/VideoStream)

# Add source files
set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        )

# Create executable
add_executable(server ${SOURCES})

# Link necessary libraries
target_link_libraries(server
        VideoStream
        ${PostgreSQL_LIBRARIES}
        ${GTEST_BOTH_LIBRARIES}
        )
