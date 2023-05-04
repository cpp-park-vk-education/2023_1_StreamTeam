#include "gtest/gtest.h"
#include <memory>
#include "room.hpp"

class RoomTest : public ::testing::Test {
protected:
    Room room;
};

TEST_F(RoomTest, TestCreatePlayer) {
    std::shared_ptr<Player> player (new Player);
    bool flag = room.CreatePlayer(player);  
    EXPECT_EQ(flag, true);
}

TEST_F(RoomTest, TestCreatePlayerNull) {
    bool flag = room.CreatePlayer(nullptr);  
    EXPECT_EQ(flag, false);
}

TEST_F(RoomTest, TestGetPlayer) {
    std::shared_ptr<Player> player (new Player);
    room.CreatePlayer(player); 
    std::shared_ptr<Player> ptr = room.GetPlayerPtr();  
    EXPECT_EQ(ptr, player);
}

TEST_F(RoomTest, TestGetPlayerNull) {
    std::shared_ptr<Player> ptr = room.GetPlayerPtr();  
    EXPECT_EQ(ptr, nullptr);
}

TEST_F(RoomTest, TestAddMember) {
    User member;
    bool flag = room.AddMember(member);
    EXPECT_EQ(flag, true);
}

// Этот тест выдает ошибку из-за отсутствия локиги проверки в самом классе, как только она появится - тест будет работать как надо
TEST_F(RoomTest, TestAddMemberIsExists) {
    User member;
    room.AddMember(member);
    bool flag = room.AddMember(member);
    EXPECT_EQ(flag, false);
}

TEST_F(RoomTest, TestDeleteMember) {
    User member;
    room.AddMember(member);
    bool flag = room.DeleteMember(member.GetId());
    EXPECT_EQ(flag, true);
}

TEST_F(RoomTest, TestAddMessage) {
    Message mes;
    bool flag = room.AddMessage(mes);
    EXPECT_EQ(flag, true);
}

TEST_F(RoomTest, TestDeleteMessage) {
    Message mes;
    room.AddMessage(mes);
    bool flag = room.DeleteMessage(mes.GetId());
    EXPECT_EQ(flag, true);
}
