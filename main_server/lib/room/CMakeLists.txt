add_library(room src/room.cpp)
target_include_directories(room PUBLIC include)
target_link_libraries(room PUBLIC session)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()