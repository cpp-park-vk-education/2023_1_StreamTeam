#include <memory>

#include "localmemory.hpp"

void LocalMemory::setCurrentUser(std::shared_ptr<User> ptr)
{
    login_user = ptr;
}

std::shared_ptr<User> LocalMemory::getCurrentUser()
{
    return login_user;
}

void LocalMemory::setCurrentRoom(std::shared_ptr<Room> ptr)
{
    current_room = ptr;
}

std::shared_ptr<Room> LocalMemory::getCurrentRoom()
{
    return current_room;
}

std::vector<std::shared_ptr<Room>>* LocalMemory::getUserRoomVectorPtr()
{
    return &user_rooms;
}

std::vector<std::shared_ptr<Message>>* LocalMemory::getMesageVectorPtr()
{
    return &current_room_messages;
}

void LocalMemory::FreeMemory()
{
    current_room.reset();
    login_user.reset();

    user_rooms.clear();
    user_rooms.shrink_to_fit();

    current_room_messages.clear();
    current_room_messages.shrink_to_fit();

}

void LocalMemory::FreeCurrentRoom()
{
    current_room.reset();

    current_room_messages.clear();
    current_room_messages.shrink_to_fit();

}
