#pragma once

#include <string>
#include <vector>

const std::string STATUS_FIELD = "status";
const std::string RESULT_FIELD = "result";
const std::string PARAMS_FIELD = "parameters";
const std::string ERROR_STATUS = "error";
const std::string SUCCESS_STATUS = "ok";

const int BOOLEAN = 16;
const int BIGINT = 20;
const int SMALLINT = 21;
const int INT = 23;
const int TEXT = 25;
const int TIME = 1083;
const int TIMESTAMP = 1114;
const int JSONB = 3802;

const std::string usersTableName = "users";
const std::vector<std::string> usersTableColumns = {"username", "email", "password"};

const std::string roomsTableName = "rooms";
const std::vector<std::string> roomsTableColumns = {"name", "creator", "current_film"};

const std::string filmsTableName = "films";
const std::vector<std::string> filmsTableColumns = {"name", "link", "data"};

const std::string messagesTableName = "messages";
const std::vector<std::string> messagesTableColumns = {"id_room", "id_user", "message", "created_at"};

const std::string viewersTableName = "viewers";
const std::vector<std::string> viewersTableColumns = {"id_user", "id_room", "points", "role"};

const std::string bidsTableName = "bids";
const std::vector<std::string> bidsTableColumns = {"id_creator", "id_room", "text", "min_points", "lifetime", "begin_time"};

const std::string votesTableName = "votes";
const std::vector<std::string> votesTableColumns = {"id_bid", "id_user", "vote", "points"};

const std::string GUEST_ROLE = "guest";
const std::string ADMIN_ROLE = "admin";
const std::string MODERATOR_ROLE = "moderator";
const std::string LEFT_ROLE = "left";
const std::string BANNED_ROLE = "banned";
