add_executable(router_test src/test_router.cpp)
target_link_libraries(router_test room router session GTest::gtest_main GTest::gmock)

add_test(router_test router_test)