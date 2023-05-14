#include "FilmsTable.hpp"

FilmsTable::FilmsTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json FilmsTable::addFilm(const json &info) const
{
    json request = {{"INTO", filmsTableName},
                    {"columns", filmsTableColumns},
                    {"VALUES", {info["name"], info["link"], info["data"]}}};

    std::cout << request << std::endl;

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        return getFilmInfo(response["result"]);
    }

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
    json request = {{"SELECT", {"*"}},
                    {"FROM", {filmsTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);
    return response;
}
