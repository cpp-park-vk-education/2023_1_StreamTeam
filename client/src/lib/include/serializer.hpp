#pragma once
#include <string>
#include <memory>
#include <vector>

#include "player.hpp"
#include "room.hpp"
#include "user.hpp"
#include "message.hpp"

using json = std::string;

class JsonDeSerializer  //  Перевод из JSON в объект.
{
public:

    bool DeSerializeMessage(Message&, json);

    bool DeSerializePlayer(Player&, json);

    bool DeSerializeRoom(Room&, json);

    bool DeSerializeUser(User&, json);

private:

};


class JsonSerializer  //  Перевод из объекта в JSON.
{
public:

    json SerializeMessage(Message&);

    json SerializePlayer(Player&);

    json SerializeRoom(Room&);

    json SerializeUser(User&);

private:

};
