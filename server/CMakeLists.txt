cmake_minimum_required(VERSION 3.10)

project(server)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.82.0 REQUIRED COMPONENTS filesystem)
include_directories(boost_test ${Boost_INCLUDE_DIRS})
find_package(Threads REQUIRED)

set(FFMPEG_LIBRARIES "/usr/lib/x86_64-linux-gnu/libavcodec.so;/usr/lib/x86_64-linux-gnu/libavformat.so;/usr/lib/x86_64-linux-gnu/libavutil.so;/usr/lib/x86_64-linux-gnu/libswscale.so")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

enable_testing()
find_package(GTest REQUIRED)


# Set include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/VideoStream/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/VideoInfo/include)
include_directories(${GTEST_INCLUDE_DIRS})

# Add subdirectories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/VideoStream)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/VideoInfo)

# Add source files
set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        )

# Create executable
add_executable(server ${SOURCES})
# Link necessary libraries
target_link_libraries(server
        VideoInfo
        VideoStream
        StreamingServer
        ${FFMPEG_LIBRARIES}
        ${Boost_LIBRARIES}
        Boost::filesystem
        ${PostgreSQL_LIBRARIES}
        ${GTEST_BOTH_LIBRARIES}
        Threads::Threads
        )
