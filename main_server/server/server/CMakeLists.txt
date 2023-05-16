add_library(server src/server.cpp)
target_include_directories(server PUBLIC include)
target_link_libraries(server PUBLIC session room database)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()