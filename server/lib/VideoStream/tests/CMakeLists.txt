add_executable(video_stream_test
                VideoEncoder/video_encoder_test.cpp
                AudioEncoder/audio_encoder_test.cpp
                VideoStream/video_stream_test.cpp
        )

target_link_libraries(video_stream_test VideoStream GTest::gtest_main)

add_test(video_stream_test video_stream_test)
