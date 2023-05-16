add_executable(video_info_test VideoInfo/video_info_test.cpp)

target_link_libraries(video_info_test VideoInfo GTest::gtest_main)

add_test(video_info_test video_info_test)
