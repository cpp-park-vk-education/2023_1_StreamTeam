cmake_minimum_required(VERSION 3.21)
project(database)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lconfig++ -lconfig -lpqxx -lpq")

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

find_library(LIBPP_LIBRARY lconfig++)
find_library(LIB_LIBRARY lconfig)


add_library(${PROJECT_NAME} src/PostgreSQL.cpp src/PostgreConnection.cpp src/UsersTable.cpp src/RoomsTable.cpp src/ViewersTable.cpp src/BidsTable.cpp src/VotesTable.cpp src/FilmsTable.cpp src/MessagesTable.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PQXX_LIB} ${PQ_LIB} config config++)
target_include_directories(${PROJECT_NAME} PUBLIC include)

set(DATABASE_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(DATABASE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)


#PATHS "usr/lib/x86_64-linux-gnu"