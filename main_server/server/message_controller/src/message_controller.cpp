#include "message_controller.hpp"

#include "response.hpp"

MessageController::MessageController(const json& request, db_ptr database,
                                     session_ptr session, room_ptr room)
    : table_(database) {
    auto itr = std::find(allowed_methods_.begin(), allowed_methods_.end(),
                         request["method"]);
    if (itr == allowed_methods_.end()) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    if (request["method"] == "addMessage") {
        AddMessage(request["data"], session, room);
    } else if (request["method"] == "deleteMessage") {
        DeleteMessage(request["data"], session, room);
    } else if (request["method"] == "updateMessage") {
        UpdateMessage(request["data"], session, room);
    } else if (request["method"] == "getMessageInfo") {
        GetMessageInfo(request["data"], session);
    } else {
        GetAllMessagesInRoom(request["data"], session);
    }
}

void MessageController::AddMessage(const json& data, session_ptr session,
                                   room_ptr room) {
    json info = table_.addMessage(data);
    if (info["status"] != "ok") {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    info["update"] = true;
    room->Send(Message(info.dump()));
}

void MessageController::DeleteMessage(const json& data, session_ptr session,
                                      room_ptr room) {
    std::size_t id;
    try {
        id = data["id"];
    } catch (std::exception& err) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    if (!table_.checkMessage(id)) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    json info = table_.deleteMessage(id);
    if (info["status"] != "ok") {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    info["update"] = true;
    room->Send(Message(info.dump()));
}

void MessageController::UpdateMessage(const json& data, session_ptr session,
                                      room_ptr room) {
    json info = table_.updateMessage(data);
    if (info["status"] != "ok") {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    info["update"] = true;
    room->Send(Message(info.dump()));
}

void MessageController::GetMessageInfo(const json& data, session_ptr session) {
    std::size_t id;
    try {
        id = data["id"];
    } catch (std::exception& err) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    json info = table_.getMessageInfo(id);
    if (info["status"] != "ok") {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    session->Send(Message(info.dump()));
}

void MessageController::GetAllMessagesInRoom(const json& data,
                                             session_ptr session) {
    std::size_t id;
    try {
        id = data["id"];
    } catch (std::exception& err) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    json info = table_.getAllMessagesInRoom(id);
    if (info["status"] != "ok") {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    session->Send(Message(info.dump()));
}
