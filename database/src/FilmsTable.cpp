#include "FilmsTable.hpp"

FilmsTable::FilmsTable(std::shared_ptr<IDatabase> _client) { client = _client; }

json FilmsTable::addFilm(const json &info) const
{
    json request = {{"INTO", filmsTableName},
                    {"columns", filmsTableColumns},
                    {"VALUES", {info["name"], info["link"], info["info"]}}};

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
    if (!checkFilm(id))
    {
        return {{STATUS_FIELD, ERROR_STATUS},
                {"msg", "A film with such ID does not exist."}};
    }
    json request = {{"FROM", filmsTableName},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->remove(request);

    return response;
}

json FilmsTable::updateFilm(const json &info) const
{
    size_t id = info["id"];
    if (!checkFilm(id))
    {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "A film with such ID does not exist."}};
    }
    json request = {{"table", filmsTableName},
                    {"SET", info["data"]},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->update(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS)
    {
        return getFilmInfo(id);
    }

    return response;
}

bool FilmsTable::checkFilm(const size_t id) const
{
    json request = {{"SELECT", {"id"}},
                    {"FROM", {filmsTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == ERROR_STATUS)
    {
        return false;
    }
    return true;
}

json FilmsTable::getFilmInfo(const size_t id) const
{
    json request = {{"SELECT", {"*"}},
                    {"FROM", {filmsTableName}},
                    {"WHERE", {"id=" + std::to_string(id)}}};

    json response = client->select(request);

    return response;
}
