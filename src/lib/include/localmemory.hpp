#ifndef LOCALMEMORY_H
#define LOCALMEMORY_H

#include "user.hpp"
#include "room.hpp"
#include "message.hpp"

#include <memory>

class LocalMemory
{
public:
    void setCurrentUser(std::shared_ptr<User>);

    std::shared_ptr<User> getCurrentUser();

    void setCurrentRoom(std::shared_ptr<Room>);

    std::shared_ptr<Room> getCurrentRoom();

    std::vector<std::shared_ptr<Room>>* getUserRoomVectorPtr();

    std::vector<std::shared_ptr<Message>>* getMesageVectorPtr();

    void FreeMemory();

    void FreeCurrentRoom();

private:
    std::shared_ptr<User> login_user;
    std::shared_ptr<Room> current_room;
    std::vector<std::shared_ptr<Room>> user_rooms;
    std::vector<std::shared_ptr<Message>> current_room_messages;

};

#endif // LOCALMEMORY_H
