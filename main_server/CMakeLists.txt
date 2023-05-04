cmake_minimum_required(VERSION 3.10)
project(hw_3)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTS "build tests" ON)
if(BUILD_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)
endif()

find_package(Boost 1.81.0 REQUIRED)
include_directories(hw_3 ${Boost_INCLUDE_DIRS})

add_subdirectory(lib/server)
add_subdirectory(lib/room)
add_subdirectory(lib/session)
add_subdirectory(lib/router)

add_executable(hw_3 src/main.cpp)
target_link_libraries(hw_3 server ${Boost_LIBRARIES})

