#include "BidsTable.hpp"

BidsTable::BidsTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json BidsTable::addBid(const json &info) const
{
    std::vector<std::string> columns(bidsTableColumns);
    json values = {info["id_creator"], info["id_room"], info["text"], info["min_points"], info["lifetime"]};

    std::cout << values << std::endl;

    if (info.contains("begin_time"))
    {
        values.push_back(info["begin_time"]);
    }
    else
    {
        columns.erase(columns.begin() + 5);
    }

    json request = {{"INTO", bidsTableName},
                    {"columns", columns},
                    {"VALUES", values}};

    std::cout << request << std::endl;

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        return getBidInfo(response["result"]);
    }

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
                    {"FROM", {bidsTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);
    return response;
}

json BidsTable::getVotesFor(const size_t id) const
{
    json request = {{"SELECT", {votesTableName + ".id"}},
                    {"FROM", {bidsTableName, votesTableName}},
                    {"WHERE", {bidsTableName + ".id=" + std::to_string(id), bidsTableName + ".id=" + votesTableName + ".id_bid", votesTableName + ".vote=TRUE"}}};

    json response = client->select(request);
    return response;
}

json BidsTable::getVotesAgainst(const size_t id) const
{
    json request = {{"SELECT", {votesTableName + ".id"}},
                    {"FROM", {bidsTableName, votesTableName}},
                    {"WHERE", {bidsTableName + ".id=" + std::to_string(id), bidsTableName + ".id=" + votesTableName + ".id_bid", votesTableName + ".vote=FALSE"}}};

    json response = client->select(request);

    return response;
}

json BidsTable::getVotesCount(const size_t id) const
{
    json request = {{"SELECT", {votesTableName + ".id"}},
                    {"FROM", {bidsTableName, votesTableName}},
                    {"WHERE", {bidsTableName + ".id=" + std::to_string(id), bidsTableName + ".id=" + votesTableName + ".id_bid"}}};

    json response = client->select(request);

    return response;
}

json BidsTable::getPointsFor(const size_t id) const
{
    json request = {{"SELECT", {"SUM(" + votesTableName + ".points)"}},
                    {"FROM", {bidsTableName, votesTableName}},
                    {"WHERE", {bidsTableName + ".id=" + std::to_string(id), bidsTableName + ".id=" + votesTableName + ".id_bid", votesTableName + ".vote=TRUE"}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        response[RESULT_FIELD] = response[RESULT_FIELD][0]["sum"];
    }

    return response;
}

json BidsTable::getPointsAgainst(const size_t id) const
{
    json request = {{"SELECT", {"SUM(" + votesTableName + ".points)"}},
                    {"FROM", {bidsTableName, votesTableName}},
                    {"WHERE", {bidsTableName + ".id=" + std::to_string(id), bidsTableName + ".id=" + votesTableName + ".id_bid", votesTableName + ".vote=FALSE"}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        response[RESULT_FIELD] = response[RESULT_FIELD][0]["sum"];
    }

    return response;
}

json BidsTable::getPointsSum(const size_t id) const
{
    json request = {{"SELECT", {"SUM(" + votesTableName + ".points)"}},
                    {"FROM", {bidsTableName, votesTableName}},
                    {"WHERE", {bidsTableName + ".id=" + std::to_string(id), bidsTableName + ".id=" + votesTableName + ".id_bid"}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        response[RESULT_FIELD] = response[RESULT_FIELD][0]["sum"];
    }

    return response;
}

json BidsTable::getWinners(const size_t id, const bool answer) const
{
    std::string strAnswer = answer ? "TRUE" : "FALSE";

    json request = {{"SELECT", {votesTableName + ".id_user"}},
                    {"FROM", {bidsTableName, votesTableName}},
                    {"WHERE", {bidsTableName + ".id=" + std::to_string(id), bidsTableName + ".id=" + votesTableName + ".id_bid", votesTableName + ".vote=" + strAnswer}}};

    json response = client->select(request);
    return response;
}
