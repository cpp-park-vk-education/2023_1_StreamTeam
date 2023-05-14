#pragma once

#include "PostgreSQL.hpp"

class VotesTable
{
public:
    VotesTable() = default;
    VotesTable(std::shared_ptr<IDatabase> client);

    json addVote(const json &info) const;
    json deleteVote(const size_t id) const;
    json updateVote(const json &info) const;
    json getVoteInfo(const size_t id) const;

private:
    std::shared_ptr<IDatabase> client;
};
