#include "user_controller.hpp"

#include "response.hpp"

UserController::UserController(const json& request, db_ptr database,
                               session_ptr session)
    : table_(database) {
    auto itr = std::find(allowed_methods_.begin(), allowed_methods_.end(),
                         request["method"]);
    if (itr == allowed_methods_.end()) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    if (request["method"] == "updateUser") {
        UpdateUser(request["data"], session);
    } else if (request["method"] == "getUserInfo") {
        GetUserInfo(request["data"], session);
    } else {
        DeleteUser(session);
    }
}

void UserController::UpdateUser(const json& data, session_ptr session) {
    json info = table_.updateUser(data);
    session->Send(Message(info.dump()));
}

void UserController::DeleteUser(session_ptr session) {
    json info = table_.deleteUser(session->GetUserId());
    if (info["status"] != "ok") {
        session->Send(NotFound());
        throw std::runtime_error{"Not Found"};
    }
    session->LeaveRoom();
    session->SetUnAuthorized();
    session->Send(NotAuthorized());
}

void UserController::GetUserInfo(const json& data, session_ptr session) {
    std::size_t id;
    try {
        id = data["id"];
    } catch (std::exception& err) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    json info = table_.getUserInfo(id);
    session->Send(Message(info.dump()));
}
