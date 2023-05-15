#include "MessagesTable.hpp"

MessagesTable::MessagesTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json MessagesTable::addMessage(const json &info) const
{
    std::vector<std::string> columnsWithoutDefault(messagesTableColumns);
    columnsWithoutDefault.erase(columnsWithoutDefault.begin() + 3);

    json request = {{"INTO", messagesTableName},
                    {"columns", columnsWithoutDefault},
                    {"VALUES", {info["id_room"], info["id_user"], info["message"]}}};

    std::cout << request << std::endl;

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        return getMessageInfo(response[RESULT_FIELD]);
    }

    return response;
}

json MessagesTable::deleteMessage(const size_t id) const
{
    if (!checkMessage(id))
    {
        return {{STATUS_FIELD, ERROR_STATUS},
                {"msg", "A message with such ID does not exist."}};
    }
    json request = {{"FROM", messagesTableName},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->remove(request);

    return response;
}

json MessagesTable::updateMessage(const json &info) const
{
    size_t id = info["id"];
    if (!checkMessage(id))
    {
        return {{STATUS_FIELD, ERROR_STATUS},
                {"msg", "A message with such ID does not exist."}};
    }
    json request = {{"table", messagesTableName},
                    {"SET", info["data"]},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->update(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        return getMessageInfo(id);
    }

    return response;
}

bool MessagesTable::checkMessage(const size_t id) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {messagesTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == ERROR_STATUS)
    {
        return false;
    }
    return true;
}

json MessagesTable::getMessageInfo(const size_t id) const
{
    json request = {{"SELECT", {"*"}},
                    {"FROM", {messagesTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);

    return response;
}

json MessagesTable::getAuthorId(const size_t id) const
{
    json request = {{"SELECT", {"id_user"}},
                    {"FROM", {messagesTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};
    json response = client->select(request);

    return response;
}
