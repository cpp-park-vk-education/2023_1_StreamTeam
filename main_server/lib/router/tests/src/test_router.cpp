#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "router.hpp"
#include "iroom.hpp"
#include "isession.hpp"

class ISession;
using session_ptr = std::shared_ptr<ISession>;


struct GMockRoom : public IRoom {
    MOCK_METHOD(void, Join, (session_ptr participant), (override));
    MOCK_METHOD(void, Leave, (session_ptr participant), (override));
    MOCK_METHOD(void, Send, (const std::string& msg), (override));
};

TEST(RouterTest, JoinRoomTest) {
    auto room = std::make_shared<GMockRoom>();
    Router router;
    EXPECT_CALL(*room, Join(::testing::An<session_ptr>()));
    router.JoinRoom(room);
}

TEST(RouterTest, LeaveRoomTest) {
    auto room = std::make_shared<GMockRoom>();
    Router router;
    EXPECT_CALL(*room, Leave(::testing::An<session_ptr>()));
    router.LeaveRoom(room);
}

TEST(RouterTest, SendMessageTest) {
    auto room = std::make_shared<GMockRoom>();
    Router router;
    EXPECT_CALL(*room, Send("Message"));
    router.SendMessage(room, "Message");
}
