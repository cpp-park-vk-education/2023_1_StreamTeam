#pragma once

#include <array>
#include <unordered_map>

#include "MessagesTable.hpp"
#include "../../../include/json.hpp"
#include "session.hpp"

using json = nlohmann::json;
using session_ptr = std::shared_ptr<Session>;
using room_ptr = std::shared_ptr<Room>;

class MessageController {
    MessagesTable table_;
    const std::array<std::string, 5> allowed_methods_{
        "addMessage", "deleteMessage", "updateMessage", "getMessageInfo",
        "getAllMessagesInRoom"};

   public:
    MessageController(const json& request, db_ptr database, session_ptr session,
                      room_ptr room);

   private:
    void AddMessage(const json& data, session_ptr session, room_ptr room);
    void DeleteMessage(const json& data, session_ptr session, room_ptr room);
    void UpdateMessage(const json& data, session_ptr session, room_ptr room);
    void GetMessageInfo(const json& data, session_ptr session);
    void GetAllMessagesInRoom(const json& data, session_ptr session);
};
