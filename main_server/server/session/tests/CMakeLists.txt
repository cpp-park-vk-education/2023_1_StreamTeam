add_executable(session_test src/test_session.cpp)
target_link_libraries(session_test session room router GTest::gtest_main GTest::gmock)

add_test(session_test session_test)