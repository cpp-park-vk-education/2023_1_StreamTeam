#include "MessagesTable.hpp"

MessagesTable::MessagesTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json MessagesTable::addMessage(const json &info) const
{
    json request = info;
    json response = client->insert(request);
    return response;
}

json MessagesTable::deleteMessage(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->remove(request);
    return response;
}

json MessagesTable::updateMessage(const json &info) const
{
    json request = info;
    json response = client->update(request);
    return response;
}

json MessagesTable::getAuthorId(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);

    return response;
}
