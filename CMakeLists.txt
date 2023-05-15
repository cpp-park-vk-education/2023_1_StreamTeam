cmake_minimum_required(VERSION 3.5)

project(SyncView VERSION 0.2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
# qt_standard_project_setup()

add_subdirectory(src/app)

add_subdirectory(src/include)

# qt_add_resources(SyncView imageresources
#    PREFIX "/images"
#    FILES logo.png
# )

