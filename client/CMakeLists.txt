cmake_minimum_required(VERSION 3.22.1)
project(HW1 VERSION 0.1.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_subdirectory(lib)

add_compile_options(-Wall -Werror -Wpedantic -Wextra)

add_executable(SyncView src/syncview.cpp)
