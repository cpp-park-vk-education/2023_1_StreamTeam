#pragma once

#include "isession.hpp"
#include "message.hpp"
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;


class ISession;
using session_ptr = std::shared_ptr<ISession>;


class IRoom {
public:
    virtual ~IRoom() = default;
    virtual void Join(session_ptr participant) = 0;
    virtual void Leave(session_ptr participant) = 0;
    virtual void Send(const Message& msg) = 0;
    virtual json GetEndpoints() = 0;
};
