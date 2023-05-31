#include "gtest/gtest.h"
#include <memory>
#include "serializer.hpp"

class SerializerTest : public ::testing::Test {
protected:
    JsonSerializer serializer;
};

class DeSerializerTest : public ::testing::Test {
protected:
    JsonDeSerializer deserializer;
};

// Тут очень много нужно будет добавить, когда будут готовы сериалайзеры
// Сериалайзеры

TEST_F(SerializerTest, TestSerMess) {
    Message mes;
    json json = serializer.SerializeMessage(mes);
    EXPECT_EQ(json, "json");
}

TEST_F(SerializerTest, TestSerRoom) {
    Room room;
    json json = serializer.SerializeRoom(room);
    EXPECT_EQ(json, "json");
}

TEST_F(SerializerTest, TestSerUser) {
    User user;
    json json = serializer.SerializeUser(user);
    EXPECT_EQ(json, "json");
}

TEST_F(SerializerTest, TestSerPlayer) {
    Player player;
    json json = serializer.SerializePlayer(player);
    EXPECT_EQ(json, "json");
}

// Десериалайзеры

TEST_F(DeSerializerTest, TestDeserMess) {
    Message mes;
    json json = "json text";
    bool flag = deserializer.DeSerializeMessage(mes, json);
    EXPECT_EQ(flag, true);
}

TEST_F(DeSerializerTest, TestDeserRoom) {
    Room room;
    json json = "json text";
    bool flag = deserializer.DeSerializeRoom(room, json);
    EXPECT_EQ(flag, true);
}

TEST_F(DeSerializerTest, TestDeserUser) {
    User user;
    json json = "json text";
    bool flag = deserializer.DeSerializeUser(user, json);
    EXPECT_EQ(flag, true);
}

TEST_F(DeSerializerTest, TestDeserPlayer) {
    Player player;
    json json = "json text";
    bool flag = deserializer.DeSerializePlayer(player, json);
    EXPECT_EQ(flag, true);
}
