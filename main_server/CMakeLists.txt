cmake_minimum_required(VERSION 3.10)
project(project)

set(CMAKE_CXX_STANDARD 20)


option(BUILD_TESTS "build tests")
if(BUILD_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)
endif()

find_package(Boost 1.81.0 REQUIRED)
include_directories(project ${Boost_INCLUDE_DIRS})
find_package(nlohmann_json 3.11.2 REQUIRED)
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)
find_package(PkgConfig)
pkg_check_modules(LIBCONFIG REQUIRED IMPORTED_TARGET libconfig++)
configure_file(src/config.cfg
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_subdirectory(server/server)
add_subdirectory(server/room)
add_subdirectory(server/session)
add_subdirectory(server/message)
add_subdirectory(server/auth)
add_subdirectory(server/film_controller)
add_subdirectory(server/message_controller)
add_subdirectory(server/response)
add_subdirectory(server/room_controller)
add_subdirectory(server/user_controller)
add_subdirectory(server/video_controller)
add_subdirectory(server/viewer_controller)
add_subdirectory(database)

add_executable(project src/main.cpp)
target_link_libraries(project server ${Boost_LIBRARIES} nlohmann_json::nlohmann_json ${PQXX_LIB} ${PQ_LIB} PkgConfig::LIBCONFIG)

