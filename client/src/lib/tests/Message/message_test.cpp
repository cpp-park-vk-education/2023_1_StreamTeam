#include "gtest/gtest.h"
#include <memory>
#include "user.hpp"
#include "message.hpp"

class MessageTest : public ::testing::Test {
protected:
    Message message;
};

TEST_F(MessageTest, TestAuthorSetGet) {
    std::shared_ptr<User> author(new User);
    author->SetName("name");
    bool flag = message.SetAuthor(author);

    EXPECT_EQ(flag, true);
    //EXPECT_EQ(message.GetAuthorName(), "name");
}

TEST_F(MessageTest, TestAuthorSetNull) {
    bool flag = message.SetAuthor(nullptr);

    EXPECT_EQ(flag, false);
    EXPECT_EQ(message.GetAuthorName(), "null author");
}

TEST_F(MessageTest, TestDeleteMethod) {
    bool flag = message.Delete();
    EXPECT_EQ(flag, true);
}
