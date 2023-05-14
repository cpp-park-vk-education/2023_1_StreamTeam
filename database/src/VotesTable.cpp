#include "VotesTable.hpp"

VotesTable::VotesTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json VotesTable::addVote(const json &info) const
{
    json request = {{"INTO", votesTableName},
                    {"columns", votesTableColumns},
                    {"VALUES", {info["id_bid"], info["id_user"], info["vote"], info["points"]}}};

    std::cout << request << std::endl;

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        return getVoteInfo(response["result"]);
    }

    return response;
}

json VotesTable::deleteVote(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->remove(request);
    return response;
}

json VotesTable::updateVote(const json &info) const
{
    json request = info;
    json response = client->update(request);
    return response;
}

json VotesTable::getVoteInfo(const size_t id) const
{
    json request = {{"SELECT", {"*"}},
                    {"FROM", {votesTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);
    return response;
}