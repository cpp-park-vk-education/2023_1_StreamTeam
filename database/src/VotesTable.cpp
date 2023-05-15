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
    if (!checkVote(id))
    {
        return {{STATUS_FIELD, ERROR_STATUS},
                {"msg", "A vote with such ID does not exist."}};
    }
    json request = {{"FROM", votesTableName},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->remove(request);

    return response;
}

json VotesTable::deleteVote(const size_t id_user, const size_t id_bid) const
{
    if (checkVote(id_user, id_bid)[STATUS_FIELD] = ERROR_STATUS)
    {
        return {{STATUS_FIELD, ERROR_STATUS},
                {"msg", "A vote with such id_user and id_bid does not exist."}};
    }
    size_t id = checkVote(id_user, id_bid)[RESULT_FIELD];

    json request = {{"FROM", votesTableName},
                    {"WHERE", {"id=" + std::to_string(id)}}};

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

bool VotesTable::checkVote(const size_t id) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {votesTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == ERROR_STATUS)
    {
        return false;
    }
    return true;
}

json VotesTable::checkVote(const size_t id_user, const size_t id_bid) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {votesTableName}},
                    {"WHERE", {"id_user=" + std::to_string(id_user), "id_bid=" + std::to_string(id_bid)}}};

    json response = client->select(request);

    return response;
}
