#pragma once

#include <set>
#include <list>
#include "iroom.hpp"

class Room : public IRoom {
public:
    void Join(session_ptr participant) override;
    void Leave(session_ptr participant) override;
    void Send(const std::string& msg) override;
private:
    std::set<session_ptr> participants_;
    std::list<std::string> queue_;
};