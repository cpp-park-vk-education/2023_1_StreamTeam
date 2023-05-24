#include "response.hpp"

#include "message.hpp"
#include "../../../include/json.hpp"

using json = nlohmann::json;

Message BadRequest() {
    json response;
    response["status"] = "error";
    return Message(response.dump());
}

Message Ok() {
    json response;
    response["status"] = "ok";
    return Message(response.dump());
}

Message NotFound() {
    json response;
    response["status"] = "error";
    return Message(response.dump());
}

Message Created() {
    json response;
    response["status"] = "ok";
    return Message(response.dump());
}

Message Forbidden() {
    json response;
    response["status"] = "error";
    return Message(response.dump());
}

Message NotAuthorized() {
    json response;
    response["status"] = "error";
    return Message(response.dump());
}
