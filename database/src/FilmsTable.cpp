#include "FilmsTable.hpp"

FilmsTable::FilmsTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json FilmsTable::addFilm(const json &info) const
{
    json request = info;
    json response = client->insert(request);
    return response;
}

json FilmsTable::deleteFilm(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->remove(request);
    return response;
}

json FilmsTable::updateFilm(const json &info) const
{
    json request = info;
    json response = client->update(request);
    return response;
}

json FilmsTable::getFilmInfo(const size_t id) const
{
    json request = {{"id", id}};
    json response = client->select(request);
    return response;
}
