add_executable(room_test src/test_room.cpp)
target_link_libraries(room_test room session GTest::gtest_main GTest::gmock)

add_test(room_test room_test)