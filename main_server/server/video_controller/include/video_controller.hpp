#pragma once

#include <array>

#include "RoomsTable.hpp"
#include "nlohmann/json.hpp"
#include "session.hpp"

using json = nlohmann::json;
using session_ptr = std::shared_ptr<Session>;
using room_ptr = std::shared_ptr<Room>;
using db_ptr = std::shared_ptr<IDatabase>;

class VideoController {
    const std::array<std::string, 3> allowed_methods{"startVideo", "pauseVideo",
                                                     "finishVideo"};
    RoomsTable table_;
    unsigned short stream_port_;

   public:
    VideoController(const json& request, db_ptr database, session_ptr session,
                    room_ptr room, unsigned short stream_port);

   private:
    void FormRequest(const std::string& status, room_ptr room,
                     session_ptr session);
    std::string SendRequest(const std::string& msg);
};