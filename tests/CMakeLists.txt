cmake_minimum_required(VERSION 3.14)
project(test_database)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lconfig++")

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

find_package(GTest REQUIRED)

message("GTEST_FOUND: ${GTEST_FOUND}")
message("GTEST_INCLUDE_DIRS: ${GTEST_INCLUDE_DIRS}")
message("GTEST_LIBRARIES: ${GTEST_LIBRARIES}")

message("DATABASE_LIBRARIES: ${DATABASE_LIBRARIES}")
message("DATABASE_INCLUDE_DIRS: ${DATABASE_INCLUDE_DIRS}")

add_executable(${PROJECT_NAME} test_database.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${DATABASE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${DATABASE_LIBRARIES} GTest::Main PkgConfig::LIBCONFIG)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_config.cfg
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

# All JSON files in the tests/data directory
file(GLOB JSON_FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/*.json)

foreach(JSON_FILE ${JSON_FILES})
  get_filename_component(FILENAME ${JSON_FILE} NAME)
  configure_file(${JSON_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${FILENAME} COPYONLY)
endforeach()

add_test(NAME test_database COMMAND test_database)
