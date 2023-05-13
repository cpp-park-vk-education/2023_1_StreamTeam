add_library(session src/session.cpp)
target_include_directories(session PUBLIC include)
target_link_libraries(session PUBLIC room router)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()