#pragma once

#include <array>

#include "RoomsTable.hpp"
#include "FilmsTable.hpp"
#include "../../../include/json.hpp"
#include "session.hpp"

using json = nlohmann::json;
using session_ptr = std::shared_ptr<Session>;
using room_ptr = std::shared_ptr<Room>;
using db_ptr = std::shared_ptr<IDatabase>;

class VideoController {
    const std::array<std::string, 3> allowed_methods{"startVideo", "pauseVideo",
                                                     "finishVideo"};
    RoomsTable table_;
    FilmsTable film_table_;

   public:
    VideoController(const json& request, db_ptr database, session_ptr session,
                    room_ptr room);

   private:
    void StartVideo(const json& data, session_ptr session, room_ptr room);
    std::string GetCommand(std::size_t room_id, std::size_t film_id, const std::string& link);
};