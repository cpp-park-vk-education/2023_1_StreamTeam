#pragma once

#include <set>
#include <list>
#include "session.hpp"
#include "message.hpp"
#include <string>
#include "../../../include/json.hpp"

class Session;
using session_ptr = std::shared_ptr<Session>;
using json = nlohmann::json;

class Room {
public:
    Room(session_ptr owner, std::size_t id) : owner_(owner), id_(id) {}

    void Join(session_ptr participant);
    void Leave(session_ptr participant);
    void Send(const Message& msg);
    void LeaveAll();

    bool IsOwner(const session_ptr& participant) const {
        return owner_ == participant;
    }

    std::size_t GetId() const {
        return id_;
    }

    json GetEndpoints();

private:
    std::set<session_ptr> participants_;
//    std::list<Message> queue_;
    session_ptr owner_;
    std::size_t id_;
};
