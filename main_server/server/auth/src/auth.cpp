#include "auth.hpp"
#include "response.hpp"
#include <iostream>
bool CheckJson(const json& request, const std::vector<std::string>& fields) {
    for (const auto& field : fields) {
        if (!request.contains(field)) {
            return false;
        }
    }
    return true;
}

Auth::Auth(const json& request, db_ptr database, session_ptr session)
        : table_(database) {
    if (!CheckJson(request, required_fields)) {
        session->Send(BadRequest());
        throw std::runtime_error{"Bad Request"};
    }
    auto itr = std::find(allowed_methods.begin(), allowed_methods.end(),
                         request["method"]);
    if (itr == allowed_methods.end()) {
        session->Send(BadRequest());
        throw std::runtime_error{"Bad Request"};
    }
    if (request["method"] == "auth") {
        CheckUser(request["data"], session);
    } else {
        CreateUser(request["data"], session);
    }
}

void Auth::CheckUser(const json& request, session_ptr session) {
    std::size_t id;
    json get_id;
    if (!CheckJson(request, required_to_check)) {
        session->Send(BadRequest());
        throw std::runtime_error{"Bad Request"};
    }
    if (request["type"] == "email" &&
        table_.checkUserByEmail(request["name"])) {
        get_id = table_.getUserIdByEmail(request["name"]);
    } else if (request["type"] == "username" &&
               table_.checkUserByUsername(request["name"])) {
        get_id = table_.getUserIdByUsername(request["name"]);
    } else {
        session->Send(NotFound());
        throw std::runtime_error{"Not Found"};
    }
    id = get_id["result"][0]["id"];
    json info = table_.getUserInfo(id);
    std::cerr << info;
    if (info["result"][0]["password"] != request["password"]) {
        session->Send(Forbidden());
        throw std::runtime_error{"Forbidden"};
    }
    session->Send(Message(info.dump()));
    session->SetAuthorized(id);
}

void Auth::CreateUser(const json& request, session_ptr session) {
    if (!CheckJson(request, required_to_register)) {
        session->Send(BadRequest());
        throw std::runtime_error{"Bad request"};
    }
    json info = table_.addUser(request);
    std::cerr << info;
    if (info["status"] == "ok") {
        session->Send(Ok());
        session->SetAuthorized(info["result"][0]["id"]);
    } else {
        session->Send(BadRequest());
        throw std::runtime_error{"Bad request"};
    }
}
