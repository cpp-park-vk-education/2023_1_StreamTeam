#pragma once

#include "isession.hpp"
#include <string>

class ISession;
using session_ptr = std::shared_ptr<ISession>;


class IRoom {
public:
    virtual ~IRoom() = default;
    virtual void Join(session_ptr participant) = 0;
    virtual void Leave(session_ptr participant) = 0;
    virtual void Send(const std::string& msg) = 0;
};
