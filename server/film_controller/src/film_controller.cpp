#include "film_controller.hpp"

#include "response.hpp"

FilmController::FilmController(const json& request, db_ptr database,
                               session_ptr session)
    : table_(database) {
    auto itr = std::find(allowed_methods_.begin(), allowed_methods_.end(),
                         request["method"]);
    if (itr == allowed_methods_.end()) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    if (request["method"] == "addFilm") {
        AddFilm(request["data"], session);
    } else if (request["method"] == "deleteFilm") {
        DeleteFilm(request["data"], session);
    } else if (request["method"] == "updateFilm") {
        UpdateFilm(request["data"], session);
    } else {
        GetFilmInfo(request["data"], session);
    }
}

void FilmController::AddFilm(const json& data, session_ptr session) {
    json info = table_.addFilm(data);
    session->Send(Message(info.dump()));
}

void FilmController::DeleteFilm(const json& data, session_ptr session) {
    json info = table_.deleteFilm(data);
    session->Send(Message(info.dump()));
}

void FilmController::UpdateFilm(const json& data, session_ptr session) {
    json info = table_.updateFilm(data);
    session->Send(Message(info.dump()));
}

void FilmController::GetFilmInfo(const json& data, session_ptr session) {
    json info = table_.getFilmInfo(data);
    session->Send(Message(info.dump()));
}
