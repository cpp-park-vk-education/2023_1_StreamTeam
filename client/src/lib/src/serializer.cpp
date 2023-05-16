#include <string>

#include "serializer.hpp"

bool JsonDeSerializer::DeSerializeMessage(Message&, json)
{
    return true;
}

bool JsonDeSerializer::DeSerializePlayer(Player&, json)
{
    return true;
}

bool JsonDeSerializer::DeSerializeRoom(Room&, json)
{
    return true;
}

bool JsonDeSerializer::DeSerializeUser(User&, json)
{
    return true;
}

json JsonSerializer::SerializeMessage(Message&)
{
    return "json";
}

json JsonSerializer::SerializePlayer(Player&)
{
    return "json";
}

json JsonSerializer::SerializeRoom(Room&)
{
    return "json";
}

json JsonSerializer::SerializeUser(User&)
{
    return "json";
}
