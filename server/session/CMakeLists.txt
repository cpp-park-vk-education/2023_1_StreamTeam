add_library(session src/session.cpp)
target_include_directories(session PUBLIC include)
target_link_libraries(session PUBLIC room message auth film_controller message_controller response room_controller user_controller video_controller viewer_controller)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()