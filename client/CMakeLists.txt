cmake_minimum_required(VERSION 3.5)

project(SyncView VERSION 0.2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Boost 1.81.0 REQUIRED)
find_package(Threads REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# qt_standard_project_setup()

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_subdirectory(src/app)

add_subdirectory(src/lib)

#add_executable(SyncView src/app/main.cpp)
target_link_libraries(SyncView ${Boost_LIBRARIES})

# qt_add_resources(SyncView imageresources
#    PREFIX "/images"
#    FILES logo.png
# )

