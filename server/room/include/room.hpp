#pragma once

#include <set>
#include <list>
#include "session.hpp"
#include "message.hpp"
#include <string>
#include "nlohmann/json.hpp"

class Session;
using session_ptr = std::shared_ptr<Session>;
using json = nlohmann::json;

class Room {
public:
    Room(std::size_t owner_id, std::size_t id) : owner_id_(owner_id), id_(id) {}

    void Join(session_ptr participant);
    void Leave(session_ptr participant);
    void Send(const Message& msg);
    void LeaveAll();

    bool IsOwner(const std::size_t& participant) const {
        return owner_id_ == participant;
    }

    std::size_t GetId() const {
        return id_;
    }

    json GetEndpoints();

private:
    std::set<session_ptr> participants_;
//    session_ptr owner_;
    std::size_t owner_id_;
    std::size_t id_;
};
