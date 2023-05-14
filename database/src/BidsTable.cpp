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

json BidsTable::getBidInfo(const size_t id) const
{
    json request = {{"SELECT", {"*"}},
                    {"FROM", {"bids"}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);
    return response;
}

json BidsTable::getVotesFor(const size_t id) const
{
    json request = {{"SELECT", {"votes.id"}},
                    {"FROM", {"bids, votes"}},
                    {"WHERE", {"bids.id=" + std::to_string(id), "bids.id = votes.id_bid", "votes.vote = TRUE"}}};

    json response = client->select(request);
    return response;
}

json BidsTable::getVotesAgainst(const size_t id) const
{
    json request = {{"SELECT", {"votes.id"}},
                    {"FROM", {"bids, votes"}},
                    {"WHERE", {"bids.id=" + std::to_string(id), "bids.id = votes.id_bid", "votes.vote = FALSE"}}};

    json response = client->select(request);

    return response;
}

json BidsTable::getVotesCount(const size_t id) const
{
    json request = {{"SELECT", {"votes.id"}},
                    {"FROM", {"bids, votes"}},
                    {"WHERE", {"bids.id=" + std::to_string(id), "bids.id = votes.id_bid"}}};

    json response = client->select(request);

    return response;
}

json BidsTable::getPointsFor(const size_t id) const
{
    json request = {{"SELECT", {"SUM(votes.points)"}},
                    {"FROM", {"bids, votes"}},
                    {"WHERE", {"bids.id=" + std::to_string(id), "bids.id = votes.id_bid", "votes.vote = TRUE"}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        response["result"] = response["result"][0]["sum"];
    }

    return response;
}

json BidsTable::getPointsAgainst(const size_t id) const
{
    json request = {{"SELECT", {"SUM(votes.points)"}},
                    {"FROM", {"bids, votes"}},
                    {"WHERE", {"bids.id=" + std::to_string(id), "bids.id = votes.id_bid", "votes.vote = FALSE"}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        response["result"] = response["result"][0]["sum"];
    }

    return response;
}

json BidsTable::getPointsSum(const size_t id) const
{
    json request = {{"SELECT", {"SUM(votes.points)"}},
                    {"FROM", {"bids, votes"}},
                    {"WHERE", {"bids.id=" + std::to_string(id), "bids.id = votes.id_bid"}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        response["result"] = response["result"][0]["sum"];
    }

    return response;
}

json BidsTable::getWinners(const size_t id, const bool answer) const
{
    std::string strAnswer = answer ? "TRUE" : "FALSE";

    json request = {{"SELECT", {"votes.id_user"}},
                    {"FROM", {"bids, votes"}},
                    {"WHERE", {"bids.id=" + std::to_string(id), "bids.id = votes.id_bid", "votes.vote=" + strAnswer}}};

    json response = client->select(request);
    return response;
}
