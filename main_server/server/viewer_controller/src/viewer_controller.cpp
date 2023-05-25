#include "response.hpp"
#include "viewer_controller.hpp"

ViewerController::ViewerController(const json& request, db_ptr database,
                                   session_ptr session, rooms_map& rooms)
        : table_(database), room_table_(database), msg_table_(database), users_table_(database) {
    auto itr = std::find(allowed_methods_.begin(), allowed_methods_.end(),
                         request["method"]);
    if (itr == allowed_methods_.end()) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    if (request["method"] == "addUserToRoom") {
        AddUserToRoom(request["data"], session, rooms);
    } else if (request["method"] == "deleteUserFromRoom") {
        DeleteUserFromRoom(session, rooms);
    } else if (request["method"] == "getUserRoleInRoom") {
        GetUserRoleInRoom(request["data"], session);
    } else if (request["method"] == "getViewersInfo") {
        GetViewersInfo(request["data"], session);
    } else if (request["method"] == "getUserRooms") {
        GetUserRooms(session);
    } else {
        GetRoomUsers(request["data"], session);
    }
}
void ViewerController::AddUserToRoom(const json& data, session_ptr session,
                                     rooms_map rooms) {
    std::size_t user_id = session->GetUserId();
    std::size_t room_id;
    try {
        room_id = data["room_id"];
    } catch (std::exception& err) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest1"};
    }
    if (!room_table_.checkRoom(room_id)) {
        session->Send(NotFound());
        throw std::runtime_error{"BadRequest2"};
    }
    if (!rooms[room_id]) {
        session->Send(NotFound());
        throw std::runtime_error{"BadRequest3"};
    }
    json info = table_.addUserToRoom(user_id, room_id);
    rooms[room_id]->Join(session);
    json msgs = msg_table_.getAllMessagesInRoom(room_id);
    json new_info = table_.getRoomUsers(room_id);
    json response;
    for (auto user: new_info["result"]) {
        user_id = user["id_user"];
        json user_info = users_table_.getUserInfo(user_id)["result"][0];
        user_info.erase("password");
        response["result"].push_back(user_info);
    }
    response["messages"] = msgs["result"];
    response["update"] = true;
    response["status"] = "ok";
    session->Send(Message(response.dump()));
    session->SetRoom(rooms[room_id]);
}
void ViewerController::DeleteUserFromRoom(session_ptr session,
                                          rooms_map rooms) {
    std::size_t user_id = session->GetUserId();
    std::size_t room_id = session->GetRoomId();
    json info = table_.deleteUserFromRoom(user_id, room_id);
    if (info["status"] == "ok") {
        session->LeaveRoom();
        info["update"] = true;
        rooms[room_id]->Send(Message(info.dump()));
    } else {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
}
void ViewerController::GetViewersInfo(const json& data, session_ptr session) {
    std::size_t id = session->GetRoomId();
    json info = table_.getViewersInfo(id);
    session->Send(Message(info.dump()));
}

void ViewerController::GetUserRoleInRoom(const json& data, session_ptr session) {
    std::size_t room_id;
    std::size_t user_id;
    try {
        room_id = data["room_id"];
        user_id = data["user_id"];
    } catch (std::exception& err) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
//    std::size_t user_id = session->GetUserId();
//    std::size_t room_id = session->GetRoomId();
    json info = table_.getUserRoleInRoom(user_id, room_id);
    session->Send(Message(info.dump()));
}

void ViewerController::GetUserRooms(session_ptr session) {
    std::size_t user_id = session->GetUserId();
    json info = table_.getUserRooms(user_id);
    session->Send(Message(info.dump()));
}

void ViewerController::GetRoomUsers(const json& data, session_ptr session) {
    std::size_t room_id;
    try {
        room_id = data["room_id"];
    } catch (std::exception& err) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
//    std::size_t room_id = session->GetRoomId();
    json info = table_.getRoomUsers(room_id);
    if (info["status"] != "ok") {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    json new_info;
    for (auto user: info["result"]) {
        std::size_t user_id = user["id_user"];
        json user_info = users_table_.getUserInfo(user_id)["result"][0];
        user_info.erase("password");
        new_info["result"].push_back(user_info);
    }
    new_info["status"] = "ok";
    session->Send(Message(new_info.dump()));
}
