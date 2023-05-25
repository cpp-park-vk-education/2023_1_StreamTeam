#include "room_controller.hpp"

#include "response.hpp"

RoomController::RoomController(const json& request, db_ptr database,
                               session_ptr session, rooms_map& rooms)
    : table_(database){
    auto itr = std::find(allowed_methods_.begin(), allowed_methods_.end(),
                         request["method"]);
    if (itr == allowed_methods_.end()) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    if (request["method"] == "addRoom") {
        AddRoom(request["data"], session, rooms);
    } else if (request["method"] == "deleteRoom") {
        DeleteRoom(request["data"], session, rooms);
    } else if (request["method"] == "updateRoom") {
        UpdateRoom(request["data"], session, rooms);
    } else if (request["method"] == "getRoomInfo") {
        GetRoomInfo(request["data"], session);
    } else {
        GetAllRooms(session);
    }
}

void RoomController::AddRoom(const json& request, session_ptr session,
                             rooms_map rooms) {
    json data = request;
    data["creator"] = session->GetUserId();
    json info = table_.addRoom(data);
    if (info["status"] != "ok") {
        session->Send(NotFound());
        throw std::runtime_error{"NotFound"};
    }
    //session->LeaveRoom();
    std::size_t id = info["result"][0]["id"];
    room_ptr room = std::make_shared<Room>(session->GetUserId(), id);
    //session->SetRoom(room);
    //room->Join(session);
    rooms[id] = room;
    session->Send(Message(info.dump()));
}

void RoomController::DeleteRoom(const json& data, session_ptr session,
                                rooms_map rooms) {
    std::size_t id;
    try {
        id = data["id"];
    } catch (std::exception& err) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    if (!rooms[id]) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    room_ptr room = rooms[id];
    if (!room->IsOwner(session->GetUserId())) {
        session->Send(Forbidden());
        throw std::runtime_error{"Forbidden"};
    }
    json info = table_.deleteRoom(id);
    info["update"] = true;
    room->Send(Message(info.dump()));
    room->LeaveAll();
    rooms.erase(id);
//        return;
//    json info = table_.getRoomInfo(id);
//    if (info["status"] != "ok") {
//        session->Send(NotFound());
//        throw std::runtime_error{"NotFound"};
//    }
//    if (info["result"][0]["creator"] != id) {
//        session->Send(Forbidden());
//        throw std::runtime_error{"Forbidden"};
//    }
//    json del_info = table_.deleteRoom(id);
//    if (del_info["status"] != "ok") {
//        session->Send(NotFound());
//        throw std::runtime_error{"NotFound"};
//    }
//    session->Send(Message(del_info.dump()));
}

void RoomController::GetRoomInfo(const json& data, session_ptr session) {
    std::size_t id;
    try {
        id = data["id"];
    } catch (std::exception& err) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    json info = table_.getRoomInfo(id);
    session->Send(Message(info.dump()));
}

void RoomController::UpdateRoom(const json& data, session_ptr session,
                                rooms_map rooms) {
    std::size_t id;
    try {
        id = data["id"];
    } catch (std::exception& err) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    if (!rooms[id]) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    json info = table_.updateRoom(id);
    info["update"] = true;
    rooms[id]->Send(Message(info.dump()));
//    if (rooms[id]) {
//        rooms[id]->Send(Message(info.dump()));
//    } else {
//        session->Send(Message(info.dump()));
//    }
}

void RoomController::GetAllRooms(session_ptr session) {
    json info = table_.getAllRooms();
    session->Send(Message(info.dump()));
}
