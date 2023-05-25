#include "video_controller.hpp"

#include <boost/asio.hpp>
#include <cstdlib>

#include "response.hpp"

using boost::asio::ip::tcp;

VideoController::VideoController(const json& request, db_ptr database,
                                 session_ptr session, room_ptr room)
    : table_(database), film_table_(database) {
    if (!room->IsOwner(session->GetUserId())) {
        //session->Send(Forbidden());
        //throw std::runtime_error{"Forbidden"};
    }
    auto itr = std::find(allowed_methods.begin(), allowed_methods.end(),
                         request["method"]);
    if (itr == allowed_methods.end()) {
        session->Send(BadRequest());
        throw std::runtime_error{"BadRequest"};
    }
    if (request["method"] == "startVideo") {
        StartVideo(request["data"], session, room);
    }
}
// {"result":[{"id":1,"info":{"description":"sss"},"link":"jdjdj","name":"Sneach"}],"status":"ok"}
// {"result":[{"current_film":1}],"status":"ok"}

void VideoController::StartVideo(const json& data, session_ptr session, room_ptr room) {
        std::size_t film_id = 1;
        std::size_t id = room->GetId();
        json film_info = film_table_.getFilmInfo(film_id);
        if (film_info["status"] != "ok") {
            session->Send(BadRequest());
            throw std::runtime_error{"BadRequest"};
        }
        std::string command = GetCommand(id, film_id, film_info["result"][0]["link"]);
        std::thread t([command] {
            std::system(command.c_str());
        });
        t.detach();
        std::string response = "rtsp://localhost:8554/" + std::to_string(id) + "_" + std::to_string(film_id);
        json resp;
        resp["status"] = "ok";
        resp["url"] = response;
        room->Send(Message(resp.dump()));
}

std::string VideoController::GetCommand(std::size_t room_id, std::size_t film_id, const std::string& link) {
    std::string chunk_1{"ffmpeg -re -stream_loop -1 -i /home/rissenberg/MediaMTX/Stream/"};
    const std::string& chunk_2 = "cat.mp4";
    std::string chunk_3{" -c copy -f rtsp rtsp://localhost:8554/"};
    std::string chunk_4 = std::to_string(room_id) + "_" + std::to_string(film_id);
    std::string command = chunk_1 + chunk_2 + chunk_3 + chunk_4;
    return command;
}

