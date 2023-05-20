cmake_minimum_required(VERSION 3.5)

project(SyncView VERSION 0.2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

find_package(Boost 1.81.0 REQUIRED)
find_package(Threads REQUIRED)
include_directories(project ${Boost_INCLUDE_DIRS})
find_package(nlohmann_json 3.11.2 REQUIRED
        CONFIG
        PATHS "/home/linuxbrew/.linuxbrew/Cellar/nlohmann-json/3.11.2/"
    )
# qt_standard_project_setup()

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_subdirectory(src/app)

add_subdirectory(src/lib)

# qt_add_resources(SyncView imageresources
#    PREFIX "/images"
#    FILES logo.png
# )

