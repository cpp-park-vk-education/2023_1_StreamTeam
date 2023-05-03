#include "VotesTable.hpp"

VotesTable::VotesTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json VotesTable::addVote(const json &info) const
{
    json request = info;
    json response = client->insert(request);
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
