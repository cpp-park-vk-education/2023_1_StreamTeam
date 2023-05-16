#pragma once

#include <array>

#include "FilmsTable.hpp"
#include "nlohmann/json.hpp"
#include "session.hpp"

using json = nlohmann::json;
using session_ptr = std::shared_ptr<Session>;
using db_ptr = std::shared_ptr<IDatabase>;

class FilmController {
    FilmsTable table_;
    const std::array<std::string, 4> allowed_methods_{
        "addFilm", "deleteFilm", "updateFilm", "getFilmInfo"};

   public:
    FilmController(const json& request, db_ptr database, session_ptr session);

   private:
    void AddFilm(const json& data, session_ptr session);
    void DeleteFilm(const json& data, session_ptr session);
    void UpdateFilm(const json& data, session_ptr session);
    void GetFilmInfo(const json& data, session_ptr session);
};
