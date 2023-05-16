add_executable(server_test src/test_server.cpp)
target_link_libraries(server_test server GTest::gtest_main)

add_test(server_test server_test)