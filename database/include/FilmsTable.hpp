#pragma once

#include "PostgreSQL.hpp"

class FilmsTable
{
public:
    FilmsTable() = default;
    FilmsTable(std::shared_ptr<IDatabase> client);

    json addFilm(const json &info) const;
    json deleteFilm(const size_t id) const;
    json updateFilm(const json &info) const;
    bool checkFilm(const size_t id) const;
    json getFilmInfo(const size_t id) const;

private:
    std::shared_ptr<IDatabase> client;
};
