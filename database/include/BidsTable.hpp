#pragma once

#include "PostgreSQL.hpp"

class BidsTable
{
public:
    BidsTable() = default;
    BidsTable(std::shared_ptr<IDatabase> client);

    json addBid(const json &info) const;
    json deleteBid(const size_t id) const;
    json updateBid(const json &info) const;
    json isEnded(const size_t id) const;
    json getVotesFor(const size_t id) const;
    json getVotesAgainst(const size_t id) const;
    json getVotesCount(const size_t id) const;
    json getPointsFor(const size_t id) const;
    json getPointsAgainst(const size_t id) const;
    json getPointsSum(const size_t id) const;
    json getWinners(const size_t id, const bool answer) const;

private:
    std::shared_ptr<IDatabase> client;
};
