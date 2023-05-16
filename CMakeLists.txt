cmake_minimum_required(VERSION 3.14)
project(syncview)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig)
pkg_check_modules(LIBCONFIG REQUIRED IMPORTED_TARGET libconfig++)

add_subdirectory(database)

add_executable(${PROJECT_NAME} main.cpp)

add_compile_options(--coverage)
add_link_options(--coverage)

option(BUILD_TESTS "build tests" OFF)
if(BUILD_TESTS)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
    enable_testing()
    add_subdirectory(tests)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${DATABASE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DATABASE_LIBRARIES})
