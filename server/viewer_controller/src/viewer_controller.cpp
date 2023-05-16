#include "response.hpp"
#include "viewer_controller.hpp"

ViewerController::ViewerController(const json& request, db_ptr database,
                                   session_ptr session, rooms_map& rooms)
    : table_(database), room_table_(database) {
    auto itr = std::find(allowed_methods_.begin(), allowed_methods_.end(),
                         request["method"]);
    if (itr == allowed_methods_.end()) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    if (request["method"] == "addUserToRoom") {
        AddUserToRoom(request["data"], session, rooms);
    } else if (request["method"] == "deleteUserFromRoom") {
        DeleteUserFromRoom(request["data"], session, rooms);
    } else if (request["method"] == "getUserRoleInRoom") {
        GetUserRoleInRoom(session);
    } else if (request["method"] == "getViewersInfo") {
        GetViewersInfo(request["data"], session);
    } else if (request["method"] == "getUserRooms") {
        GetUserRooms(session);
    } else {
        GetRoomUsers(session);
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
        throw std::runtime_error{"BadRequest"};
    }
    if (!room_table_.checkRoom(room_id)) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    if (!rooms[room_id]) {
        room_ptr room = std::make_shared<Room>(session, room_id);
        json info = table_.addUserToRoom(user_id, room_id);
        rooms[room_id] = room;
        room->Join(session);
        room->Send(Message(info.dump()));
        return;
    }
    json info = table_.addUserToRoom(user_id, room_id);
    if (info["status"] == "ok") {
        rooms[room_id]->Join(session);
        rooms[room_id]->Send(Message(info.dump()));
        session->SetRoom(rooms[room_id]);
    } else {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
}
void ViewerController::DeleteUserFromRoom(const json& data, session_ptr session,
                                          rooms_map rooms) {
    std::size_t user_id = session->GetUserId();
    std::size_t room_id = session->GetRoomId();
    json info = table_.deleteUserFromRoom(user_id, room_id);
    if (info["status"] == "ok") {
        session->LeaveRoom();
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

void ViewerController::GetUserRoleInRoom(session_ptr session) {
    std::size_t user_id = session->GetUserId();
    std::size_t room_id = session->GetRoomId();
    json info = table_.getUserRoleInRoom(user_id, room_id);
    session->Send(Message(info.dump()));
}

void ViewerController::GetUserRooms(session_ptr session) {
    std::size_t user_id = session->GetUserId();
    json info = table_.getUserRooms(user_id);
    session->Send(Message(info.dump()));
}

void ViewerController::GetRoomUsers(session_ptr session) {
    std::size_t room_id = session->GetRoomId();
    json info = table_.getRoomUsers(room_id);
    session->Send(Message(info.dump()));
}
