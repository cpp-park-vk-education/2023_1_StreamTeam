#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "room.hpp"
#include "isession.hpp"


struct GMockSession : public ISession {
    MOCK_METHOD(void, Send, (const std::string& msg), (override));
    MOCK_METHOD(void, Run, (), (override));
};

TEST(RoomTest, SendMessageAfterJoinTest) {
    auto session = std::make_shared<GMockSession>();
    Room room;
    room.Send("Message");
    EXPECT_CALL(*session, Send("Message"));
    room.Join(session);
}

