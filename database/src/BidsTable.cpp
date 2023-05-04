#include "BidsTable.hpp"

BidsTable::BidsTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json BidsTable::addBid(const json &info) const
{
    json request = info;
    json response = client->insert(request);
    return response;
}

json BidsTable::deleteBid(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->remove(request);
    return response;
}

json BidsTable::updateBid(const json &info) const
{
    json request = info;
    json response = client->update(request);
    return response;
}

json BidsTable::isEnded(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);
    return response;
}

json BidsTable::getVotesFor(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);

    return response;
}

json BidsTable::getVotesAgainst(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);

    return response;
}

json BidsTable::getVotesCount(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);

    return response;
}

json BidsTable::getPointsFor(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);

    return response;
}

json BidsTable::getPointsAgainst(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);

    return response;
}

json BidsTable::getPointsSum(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);

    return response;
}

json BidsTable::getWinners(const size_t id, const bool answer) const
{
    json request = {{"id", id},
                    {"answer", answer}};
    json response = client->select(request);
    return response;
}
