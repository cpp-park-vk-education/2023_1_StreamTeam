add_library(message src/message.cpp)
target_include_directories(message PUBLIC include)
#target_link_libraries(server PUBLIC session room)

#if(BUILD_TESTS)
#    add_subdirectory(tests)
#endif()