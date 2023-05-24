cmake_minimum_required(VERSION 3.21)
project(project)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTS "build tests")
if(BUILD_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)
endif()

find_package(Boost 1.81.0 REQUIRED)
find_package(Threads REQUIRED)
include_directories(project ${Boost_INCLUDE_DIRS})
find_package(nlohmann_json 3.11.2 REQUIRED)

find_path(libpqxx_INCLUDE_DIR usr/include/pqxx/pqxx)
include(SelectLibraryConfigurations)
find_library(libpqxx_LIBRARY_RELEASE NAMES libpqxx)
find_library(libpqxx_LIBRARY_DEBUG NAMES libpqxxd)
select_library_configurations(libpqxx)

find_path(LIB_LIB_DIR /usr/include/libconfig.h++)
find_library(LIB_LIBPP_LIBRARY NAMES libconfig++)
find_library(LIB_LIB_LIBRARY NAMES libconfig PATHS "/usr/lib/x86_64-linux-gnu")

configure_file(src/config.cfg
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
        
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lconfig -lconfig++ -pthread -lpqxx -lpq")

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

target_include_directories(${PROJECT_NAME} PUBLIC ${DATABASE_INCLUDE_DIRS})

target_link_libraries(project server ${Boost_LIBRARIES} nlohmann_json::nlohmann_json ${DATABASE_LIBRARIES})
