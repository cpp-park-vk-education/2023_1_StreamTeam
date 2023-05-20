#include "room.hpp"


void Room::Join(session_ptr participant) {
    participants_.insert(participant);
    participant->SetRoomId(id_);
    json data;
}

void Room::Leave(session_ptr participant) {
    if (participant->GetUserId() == owner_id_) {
        LeaveAll();
    } else {
        participants_.erase(participant);
    }

}

void Room::LeaveAll() {
    for (const auto& participant : participants_) {
        participants_.erase(participant);
    }
}

void Room::Send(const Message& msg) {
    for (const auto& participant : participants_) participant->Send(msg);
}

json Room::GetEndpoints() {
    json endpoints;
    for (const auto& participant : participants_) {
        endpoints.push_back(participant->GetUserEndpoint());
    }
    return endpoints;
}