#pragma once

#include "PostgreSQL.hpp"

class MessagesTable
{
public:
    MessagesTable() = default;
    MessagesTable(std::shared_ptr<IDatabase> client);

    json addMessage(const json &info) const;
    json deleteMessage(const size_t id) const;
    json updateMessage(const json &info) const;
    bool checkMessage(const size_t id) const;
    json getMessageInfo(const size_t id) const;
    json getAuthorId(const size_t id) const;
    json getAllMessagesInRoom(const size_t id_room) const;

private:
    std::shared_ptr<IDatabase> client;
};
