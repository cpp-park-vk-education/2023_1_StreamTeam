#include "gtest/gtest.h"
#include <memory>
#include "user.hpp"

class UserTest : public ::testing::Test {
protected:
    User user;
};

TEST_F(UserTest, TestSetActivePlayer) {
    std::shared_ptr<Player> player (new Player);
    bool flag = user.SetActivePlayer(player);  
    EXPECT_EQ(flag, true);
}

TEST_F(UserTest, TestSetActivePlayerNull) {
    bool flag = user.SetActivePlayer(nullptr);  
    EXPECT_EQ(flag, false);
}

TEST_F(UserTest, TestGetActivePlayer) {
    std::shared_ptr<Player> player (new Player);
    user.SetActivePlayer(player);
    std::shared_ptr<Player> ptr = user.GetActivePlayer();
    EXPECT_EQ(ptr, player);
}