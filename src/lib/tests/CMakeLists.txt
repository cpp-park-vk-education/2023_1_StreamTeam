add_executable(classes_test
                Message/message_test.cpp
                Player/player_test.cpp
                Room/room_test.cpp
                Serializer/serializer_test.cpp
                User/user_test.cpp
            )

target_link_libraries(classes_test UserInterface GTest::gtest_main)

add_test(classes_test classes_test)
