add_library(router src/router.cpp)
target_include_directories(router PUBLIC include)
target_link_libraries(router PUBLIC room session)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()