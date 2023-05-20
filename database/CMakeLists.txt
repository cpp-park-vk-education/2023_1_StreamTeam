#cmake_minimum_required(VERSION 3.0.0)
#project(database)
#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")



add_library(database src/PostgreSQL.cpp src/PostgreConnection.cpp src/UsersTable.cpp src/RoomsTable.cpp src/ViewersTable.cpp src/BidsTable.cpp src/VotesTable.cpp src/FilmsTable.cpp src/MessagesTable.cpp)

target_include_directories(database PUBLIC include)

set(DATABASE_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(DATABASE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
