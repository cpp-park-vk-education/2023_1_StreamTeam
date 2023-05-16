#include "response.hpp"

#include "message.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

Message BadRequest() {
    json response;
    response["status"] = "bad request";
    return Message(response.dump());
}

Message Ok() {
    json response;
    response["status"] = "ok";
    return Message(response.dump());
}

Message NotFound() {
    json response;
    response["status"] = "not found";
    return Message(response.dump());
}

Message Created() {
    json response;
    response["status"] = "created";
    return Message(response.dump());
}

Message Forbidden() {
    json response;
    response["status"] = "forbidden";
    return Message(response.dump());
}

Message NotAuthorized() {
    json response;
    response["status"] = "not authorized";
    return Message(response.dump());
}
