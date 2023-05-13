#pragma once

class ISession {
public:
    virtual ~ISession() = default;
    virtual void Send(const std::string& msg) = 0;
    virtual void Run() = 0;
};