#include <fstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "PostgreSQL.hpp"
#include "UsersTable.hpp"
#include "RoomsTable.hpp"
#include "ViewersTable.hpp"
#include "BidsTable.hpp"
#include "VotesTable.hpp"
#include "FilmsTable.hpp"

const std::string TEST_PATH = "test_config.cfg";
const std::string USERS_DATA_PATH = "users_data.json";
const std::string ROOMS_DATA_PATH = "rooms_data.json";
const std::string VIEWERS_DATA_PATH = "viewers_data.json";
const std::string BIDS_DATA_PATH = "bids_data.json";
const std::string VOTES_DATA_PATH = "votes_data.json";
const std::string FILMS_DATA_PATH = "films_data.json";

class BaseTestConnection : public ::testing::Test
{
protected:
    void SetUp() override
    {
        connection = std::make_shared<PostgreConnection>(TEST_PATH);
        client = std::make_shared<PostgreSQL>(connection);
    }

    static json getData(const std::string &path)
    {
        std::ifstream input(path);
        if (!input.is_open())
        {
            throw std::runtime_error("Failed to open " + path);
        }

        json data;
        try
        {
            data = json::parse(input);
        }
        catch (std::exception &e)
        {
            throw std::runtime_error("Failed to read " + path);
        }
        return data;
    }

    static inline std::shared_ptr<PostgreSQL> client;
    static inline std::shared_ptr<PostgreConnection> connection;
};

class UsersTableTest : public BaseTestConnection
{
public:
    static UsersTable getUsersTable()
    {
        UsersTable table(client);
        return table;
    }

    static json getUsers()
    {
        return getData(USERS_DATA_PATH);
    }
};

class RoomsTableTest : public BaseTestConnection
{
public:
    static RoomsTable getRoomsTable()
    {
        RoomsTable table(client);
        return table;
    }

    static json getRooms()
    {
        return getData(ROOMS_DATA_PATH);
    }
};

class ViewersTableTest : public BaseTestConnection
{
public:
    static ViewersTable getViewersTable()
    {
        ViewersTable table(client);
        return table;
    }

    static json getViewers()
    {
        return getData(VIEWERS_DATA_PATH);
    }
};

class BidsTableTest : public BaseTestConnection
{
public:
    static BidsTable getBidsTable()
    {
        BidsTable table(client);
        return table;
    }

    static json getBids()
    {
        return getData(BIDS_DATA_PATH);
    }

    static json getVotes()
    {
        return getData(VOTES_DATA_PATH);
    }
};

class VotesTableTest : public BaseTestConnection
{
public:
    static VotesTable getVotesTable()
    {
        VotesTable table(client);
        return table;
    }

    static json getVotes()
    {
        return getData(VOTES_DATA_PATH);
    }
};

class FilmsTableTest : public BaseTestConnection
{
public:
    static FilmsTable getFilmsTable()
    {
        FilmsTable table(client);
        return table;
    }

    static json getFilms()
    {
        return getData(FILMS_DATA_PATH);
    }
};

TEST_F(UsersTableTest, addUserNotExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    json request = {{"username", "test1"}, {"email", "test1@mail.ru"}, {"password", "test1"}};
    json response = table.addUser(request);

    json users = UsersTableTest::getUsers();
    size_t id = users.size();

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id"], id + 1);
    EXPECT_EQ(response[RESULT_FIELD][0]["username"], request["username"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["email"], request["email"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["password"], request["password"]);
}

TEST_F(UsersTableTest, addUserExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    json request = {{"username", "lexus"}, {"email", "lexus@mail.ru"}, {"password", "lexus"}};
    json response = table.addUser(request);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(UsersTableTest, deleteUserExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    json users = UsersTableTest::getUsers();
    size_t id = users.size();

    json response = table.deleteUser(id + 1);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
}

TEST_F(UsersTableTest, deleteUserNotExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    json response = table.deleteUser(10);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(UsersTableTest, updateUserExist)
{
    UsersTable table = UsersTableTest::getUsersTable();
    size_t id = 4;

    json request = {{"id", id}, {"data", {{"username", "test1"}, {"email", "test1@mail.ru"}, {"password", "test1"}}}};
    json response = table.updateUser(request);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id"], id);
    EXPECT_EQ(response[RESULT_FIELD][0]["username"], request["data"]["username"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["email"], request["data"]["email"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["password"], request["data"]["password"]);
}

TEST_F(UsersTableTest, updateUserNotExist)
{
    UsersTable table = UsersTableTest::getUsersTable();
    size_t id = 10;

    json request = {{"id", id}, {"data", {{"username", "test1"}, {"email", "test1@mail.ru"}, {"password", "test1"}}}};
    json response = table.updateUser(request);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(UsersTableTest, checkUserByIDExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    bool response = table.checkUserByID(1);

    EXPECT_EQ(response, true);
}

TEST_F(UsersTableTest, checkUserByIDNotExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    bool response = table.checkUserByID(10);

    EXPECT_EQ(response, false);
}

TEST_F(UsersTableTest, checkUserByEmailExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    bool response = table.checkUserByEmail("lexus@mail.ru");

    EXPECT_EQ(response, true);
}

TEST_F(UsersTableTest, checkUserByEmailNotExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    bool response = table.checkUserByEmail("test@test.test");

    EXPECT_EQ(response, false);
}

TEST_F(UsersTableTest, checkUserByUsernameExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    bool response = table.checkUserByUsername("lexus");

    EXPECT_EQ(response, true);
}

TEST_F(UsersTableTest, checkUserByUsernameNotExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    bool response = table.checkUserByUsername("test");

    EXPECT_EQ(response, false);
}

TEST_F(UsersTableTest, getUserInfoExist)
{
    UsersTable table = UsersTableTest::getUsersTable();
    size_t id = 0;

    json response = table.getUserInfo(id + 1);

    json users = UsersTableTest::getUsers();

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][id]["id"], id + 1);
    EXPECT_EQ(response[RESULT_FIELD][id]["username"], users[id]["username"]);
    EXPECT_EQ(response[RESULT_FIELD][id]["email"], users[id]["email"]);
    EXPECT_EQ(response[RESULT_FIELD][id]["password"], users[id]["password"]);
}

TEST_F(UsersTableTest, getUserInfoNotExist)
{
    UsersTable table = UsersTableTest::getUsersTable();
    size_t id = 10;

    json response = table.getUserInfo(id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(RoomsTableTest, addRoom)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    json request = {{"name", "test"}, {"creator", 4}, {"current_film", nullptr}};
    json response = table.addRoom(request);

    json rooms = RoomsTableTest::getRooms();
    size_t id = rooms.size();

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id"], id + 1);
    EXPECT_EQ(response[RESULT_FIELD][0]["name"], request["name"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["creator"], request["creator"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["current_film"], request["current_film"]);
}

TEST_F(RoomsTableTest, deleteRoomExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    json rooms = RoomsTableTest::getRooms();
    size_t id = rooms.size();

    json response = table.deleteRoom(id + 1);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
}

TEST_F(RoomsTableTest, deleteRoomNotExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    json response = table.deleteRoom(10);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(RoomsTableTest, updateRoomExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    size_t id = 2;

    json request = {{"id", id}, {"data", {{"name", "test"}, {"creator", 3}}}};
    json response = table.updateRoom(request);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id"], id);
    EXPECT_EQ(response[RESULT_FIELD][0]["name"], request["data"]["name"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["creator"], request["data"]["creator"]);
}

TEST_F(RoomsTableTest, updateRoomNotExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    size_t id = 10;

    json request = {{"id", id}, {"data", {{"name", "test"}, {"creator", 2}}}};
    json response = table.updateRoom(request);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(RoomsTableTest, checkRoomExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    bool response = table.checkRoom(1);

    EXPECT_EQ(response, true);
}

TEST_F(RoomsTableTest, checkRoomNotExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    bool response = table.checkRoom(10);

    EXPECT_EQ(response, false);
}

TEST_F(RoomsTableTest, getRoomInfoExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    size_t id = 0;

    json response = table.getRoomInfo(id + 1);

    json rooms = RoomsTableTest::getRooms();

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][id]["id"], id + 1);
    EXPECT_EQ(response[RESULT_FIELD][id]["name"], rooms[id]["name"]);
    EXPECT_EQ(response[RESULT_FIELD][id]["creator"], rooms[id]["creator"]);
    EXPECT_EQ(response[RESULT_FIELD][id]["current_film"], rooms[id]["current_film"]);
}

TEST_F(RoomsTableTest, getRoomInfoNotExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    size_t id = 10;

    json response = table.getRoomInfo(id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(RoomsTableTest, getAllRooms)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    json response = table.getAllRooms();

    json rooms = RoomsTableTest::getRooms();

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD].size(), rooms.size());
}

TEST_F(RoomsTableTest, getCurrentFilmExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    size_t id = 0;

    json response = table.getCurrentFilm(id + 1);

    json rooms = RoomsTableTest::getRooms();

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][id]["current_film"], rooms[id]["current_film"]);
}

TEST_F(RoomsTableTest, getCurrentFilmNotExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    size_t id = 10;

    json response = table.getCurrentFilm(id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(RoomsTableTest, checkCurrentFilmExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    json response = table.checkCurrentFilm(1);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD], true);
}

TEST_F(RoomsTableTest, checkCurrentFilmExistButNull)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    json response = table.checkCurrentFilm(2);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD], false);
}

TEST_F(RoomsTableTest, checkCurrentFilmNotExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    json response = table.checkCurrentFilm(10);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(ViewersTableTest, getUserRoomsExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 2;

    json response = table.getUserRooms(id);
    std::vector<int> actual_rooms;

    for (size_t i = 0; i < response[RESULT_FIELD].size(); ++i)
    {
        actual_rooms.push_back(response[RESULT_FIELD][i]["id_room"]);
    }

    json viewers = ViewersTableTest::getViewers();
    std::vector<int> expected_rooms;

    for (size_t i = 0; i < viewers.size(); ++i)
    {
        if (viewers[i]["id_user"] == id)
        {
            expected_rooms.push_back(viewers[i]["id_room"]);
        }
    }

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(actual_rooms.size(), expected_rooms.size());
    EXPECT_EQ(actual_rooms[0], expected_rooms[0]);
}

TEST_F(ViewersTableTest, getUserRoomsNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 10;

    json response = table.getUserRooms(id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(ViewersTableTest, getRoomUsersExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 1;

    json response = table.getRoomUsers(id);
    std::vector<int> actual_users;

    for (size_t i = 0; i < response[RESULT_FIELD].size(); ++i)
    {
        actual_users.push_back(response[RESULT_FIELD][i]["id_user"]);
    }

    json viewers = ViewersTableTest::getViewers();
    std::vector<int> expected_users;

    for (size_t i = 0; i < viewers.size(); ++i)
    {
        if (viewers[i]["id_room"] == id)
        {
            expected_users.push_back(viewers[i]["id_user"]);
        }
    }

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(actual_users.size(), expected_users.size());
    EXPECT_EQ(actual_users[0], expected_users[0]);
}

TEST_F(ViewersTableTest, getRoomUsersNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 10;

    json response = table.getRoomUsers(id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(ViewersTableTest, addUserToRoomExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id_user = 1;
    size_t id_room = 2;

    json response = table.addUserToRoom(id_user, id_room);

    json viewers = ViewersTableTest::getViewers();
    size_t id = viewers.size();

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id"], id + 1);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_user"], id_user);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_room"], id_room);
    EXPECT_EQ(response[RESULT_FIELD][0]["points"], 0);
    EXPECT_EQ(response[RESULT_FIELD][0]["role"], GUEST_ROLE);
}

TEST_F(ViewersTableTest, addUserToRoomNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 10;

    json response = table.addUserToRoom(id, id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(ViewersTableTest, getUserPointsInRoomExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    json viewers = ViewersTableTest::getViewers();
    size_t id = 1;
    size_t expected_points;

    json response = table.getUserPointsInRoom(id, id);

    for (size_t i = 0; i < viewers.size(); ++i)
    {
        if (viewers[i]["id_user"] == id & viewers[i]["id_room"] == id)
        {
            expected_points = viewers[i]["points"];
        }
    }

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD], expected_points);
}

TEST_F(ViewersTableTest, getUserPointsInRoomNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    json viewers = ViewersTableTest::getViewers();
    size_t id = 10;

    json response = table.getUserPointsInRoom(id, id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(ViewersTableTest, setUserPointsInRoomExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id_user = 1;
    size_t id_room = 1;
    size_t new_points = 1000;

    json response = table.setUserPointsInRoom(id_user, id_room, new_points);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_user"], id_user);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_user"], id_room);
    EXPECT_EQ(response[RESULT_FIELD][0]["points"], new_points);
}

TEST_F(ViewersTableTest, setUserPointsInRoomNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 10;
    size_t new_points = 1000;

    json response = table.setUserPointsInRoom(id, id, new_points);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(ViewersTableTest, getUserRoleInRoomExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    json viewers = ViewersTableTest::getViewers();
    size_t id = 1;
    std::string expected_role;

    json response = table.getUserRoleInRoom(id, id);

    for (size_t i = 0; i < viewers.size(); ++i)
    {
        if (viewers[i]["id_user"] == id & viewers[i]["id_room"] == id)
        {
            expected_role = viewers[i]["role"];
        }
    }

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD], expected_role);
}

TEST_F(ViewersTableTest, getUserRoleInRoomNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    json viewers = ViewersTableTest::getViewers();
    size_t id = 10;

    json response = table.getUserRoleInRoom(id, id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(ViewersTableTest, setUserRoleInRoomExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id_user = 1;
    size_t id_room = 1;
    std::string new_role = BANNED_ROLE;

    json response = table.setUserRoleInRoom(id_user, id_room, new_role);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_user"], id_user);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_user"], id_room);
    EXPECT_EQ(response[RESULT_FIELD][0]["role"], new_role);
}

TEST_F(ViewersTableTest, setUserRoleInRoomExist_INVALID)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 1;
    std::string new_role = "something";

    json response = table.setUserRoleInRoom(id, id, new_role);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(ViewersTableTest, setUserRoleInRoomNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 10;
    std::string new_role = GUEST_ROLE;

    json response = table.setUserRoleInRoom(id, id, new_role);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(BidsTableTest, addBid)
{
    BidsTable table = BidsTableTest::getBidsTable();

    json request = {{"id_creator", 2}, {"id_room", 1}, {"text", "test"}, {"min_points", 10}, {"begin_time", "2023-03-12 10:10:10"}, {"lifetime", "04:30:00"}};
    json response = table.addBid(request);

    json bids = BidsTableTest::getBids();
    size_t id = bids.size();

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id"], id + 1);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_creator"], request["id_creator"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_room"], request["id_room"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["text"], request["text"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["min_points"], request["min_points"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["begin_time"], request["begin_time"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["lifetime"], request["lifetime"]);
}

TEST_F(BidsTableTest, deleteBidExist)
{
    BidsTable table = BidsTableTest::getBidsTable();

    json bids = BidsTableTest::getBids();
    size_t id = bids.size();

    json response = table.deleteBid(id + 1);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
}

TEST_F(BidsTableTest, deleteBidNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();

    json response = table.deleteBid(10);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(BidsTableTest, updateBidExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 2;

    json request = {{"id", id}, {"data", {{"id_creator", 2}, {"id_room", 1}, {"text", "test"}, {"min_points", 10}, {"begin_time", "2023-03-12 10:10:10"}, {"lifetime", "04:30:00"}}}};
    json response = table.updateBid(request);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id"], id);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_creator"], request["data"]["id_creator"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_room"], request["data"]["id_room"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["text"], request["data"]["text"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["min_points"], request["data"]["min_points"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["begin_time"], request["data"]["begin_time"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["lifetime"], request["data"]["lifetime"]);
}

TEST_F(BidsTableTest, updateBidNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json request = {{"id", id}, {"data", {{"id_creator", 2}, {"id_room", 1}, {"text", "test"}, {"min_points", 10}, {"begin_time", "2023-03-12 10:10:10"}, {"lifetime", "04:30:00"}}}};
    json response = table.updateBid(request);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(BidsTableTest, getVotesForExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 1;

    json votes = BidsTableTest::getVotes();
    size_t counter = 0;

    for (size_t i = 0; i < votes.size(); ++i)
    {
        if (votes[i]["id_bid"] == id & votes[i]["vote"] == true)
        {
            counter++;
        }
    }

    json response = table.getVotesFor(id);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD].size(), counter);
}

TEST_F(BidsTableTest, getVotesForNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getVotesFor(id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(BidsTableTest, getVotesAgainstExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 1;

    json votes = BidsTableTest::getVotes();
    size_t counter = 0;

    for (size_t i = 0; i < votes.size(); ++i)
    {
        if (votes[i]["id_bid"] == id & votes[i]["vote"] == false)
        {
            counter++;
        }
    }

    json response = table.getVotesAgainst(id);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD].size(), counter);
}

TEST_F(BidsTableTest, getVotesAgainstNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getVotesAgainst(id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(BidsTableTest, getVotesCountExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 1;

    json votes = BidsTableTest::getVotes();
    size_t counter = 0;

    for (size_t i = 0; i < votes.size(); ++i)
    {
        if (votes[i]["id_bid"] == id)
        {
            counter++;
        }
    }

    json response = table.getVotesCount(id);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD].size(), counter);
}

TEST_F(BidsTableTest, getVotesCountNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getVotesCount(id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(BidsTableTest, getPointsForExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 1;

    json votes = BidsTableTest::getVotes();
    size_t sum = 0;

    for (size_t i = 0; i < votes.size(); ++i)
    {
        if (votes[i]["id_bid"] == id & votes[i]["vote"] == true)
        {
            sum += votes[i]["points"].get<int>();
        }
    }

    json response = table.getPointsFor(id);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD], sum);
}

TEST_F(BidsTableTest, getPointsForNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getPointsFor(id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(BidsTableTest, getPointsAgainstExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 1;

    json votes = BidsTableTest::getVotes();
    size_t sum = 0;

    for (size_t i = 0; i < votes.size(); ++i)
    {
        if (votes[i]["id_bid"] == id & votes[i]["vote"] == false)
        {
            sum += votes[i]["points"].get<int>();
        }
    }

    json response = table.getPointsAgainst(id);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD], sum);
}

TEST_F(BidsTableTest, getPointsAgainstNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getPointsAgainst(id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(BidsTableTest, getPointsSumExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 1;

    json votes = BidsTableTest::getVotes();
    size_t sum = 0;

    for (size_t i = 0; i < votes.size(); ++i)
    {
        if (votes[i]["id_bid"] == id)
        {
            sum += votes[i]["points"].get<int>();
        }
    }

    json response = table.getPointsSum(id);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD], sum);
}

TEST_F(BidsTableTest, getPointsCountNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getPointsSum(id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(BidsTableTest, getWinnersExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 1;
    bool answer = true;
    std::vector<size_t> winners;

    json votes = BidsTableTest::getVotes();

    for (size_t i = 0; i < votes.size(); ++i)
    {
        if (votes[i]["id_bid"] == id & votes[i]["vote"] == answer)
        {
            winners.push_back(votes[i]["id_user"]);
        }
    }

    json response = table.getWinners(id, answer);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD].size(), winners.size());
    EXPECT_EQ(response[RESULT_FIELD][0]["id_user"], winners[0]);
}

TEST_F(BidsTableTest, getWinnersNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getWinners(id, true);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(VotesTableTest, addVoteNotExist)
{
    VotesTable table = VotesTableTest::getVotesTable();

    json request = {{"id_bid", 2}, {"id_user", 2}, {"vote", false}, {"points", 100}};
    json response = table.addVote(request);

    json votes = VotesTableTest::getVotes();
    size_t id = votes.size();

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id"], id + 1);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_bid"], request["id_bid"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_user"], request["id_user"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["vote"], request["vote"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["points"], request["points"]);
}

TEST_F(VotesTableTest, addVoteExist)
{
    VotesTable table = VotesTableTest::getVotesTable();

    json request = {{"id_bid", 1}, {"id_user", 1}, {"vote", false}, {"points", 100}};
    json response = table.addVote(request);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(VotesTableTest, deleteVoteExist)
{
    VotesTable table = VotesTableTest::getVotesTable();

    json votes = VotesTableTest::getVotes();
    size_t id = votes.size();

    json response = table.deleteVote(id + 1);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
}

TEST_F(VotesTableTest, deleteVoteNotExist)
{
    VotesTable table = VotesTableTest::getVotesTable();

    json response = table.deleteVote(10);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(VotesTableTest, updateVoteExist)
{
    VotesTable table = VotesTableTest::getVotesTable();
    size_t id = 4;

    json request = {{"id", id}, {"data", {{"id_bid", 1}, {"id_user", 4}, {"vote", false}, {"points", 100}}}};
    json response = table.updateVote(request);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id"], id);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_bid"], request["data"]["id_bid"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["id_user"], request["data"]["id_user"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["vote"], request["data"]["vote"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["points"], request["data"]["points"]);
}

TEST_F(VotesTableTest, updateVoteNotExist)
{
    VotesTable table = VotesTableTest::getVotesTable();
    size_t id = 10;

    json request = {{"id", id}, {"data", {{"id_bid", 1}, {"id_user", 1}, {"vote", false}, {"points", 100}}}};
    json response = table.updateVote(request);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(FilmsTableTest, addFilm)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();

    json request = {{"name", "test"}, {"link", "https://www.test.ru/test"}, {"info", {{"description", "test"}}}};
    json response = table.addFilm(request);

    json films = FilmsTableTest::getFilms();
    size_t id = films.size();

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id"], id + 1);
    EXPECT_EQ(response[RESULT_FIELD][0]["name"], request["name"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["link"], request["link"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["info"]["description"], request["info"]["description"]);
}

TEST_F(FilmsTableTest, deleteFilmExist)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();

    json films = FilmsTableTest::getFilms();
    size_t id = films.size();

    json response = table.deleteFilm(id + 1);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
}

TEST_F(FilmsTableTest, deleteFilmNotExist)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();

    json response = table.deleteFilm(10);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(FilmsTableTest, updateFilmExist)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();
    size_t id = 2;

    json request = {{"id", id}, {"data", {{"name", "test"}, {"link", "https://www.test.ru/test"}, {"info", {{"description", "test"}}}}}};
    json response = table.updateFilm(request);

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][0]["id"], id);
    EXPECT_EQ(response[RESULT_FIELD][0]["name"], request["data"]["name"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["link"], request["data"]["link"]);
    EXPECT_EQ(response[RESULT_FIELD][0]["info"]["description"], request["data"]["info"]["description"]);
}

TEST_F(FilmsTableTest, updateFilmNotExist)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();
    size_t id = 10;

    json request = {{"id", id}, {"data", {{"name", "test"}, {"link", "https://www.test.ru/test"}, {"info", {{"description", "test"}}}}}};
    json response = table.updateFilm(request);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}

TEST_F(FilmsTableTest, getFilmInfoExist)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();
    size_t id = 0;

    json response = table.getFilmInfo(id + 1);

    json films = FilmsTableTest::getFilms();

    EXPECT_EQ(response[STATUS_FIELD], SUCCESS_STATUS);
    EXPECT_EQ(response[RESULT_FIELD][id]["id"], id + 1);
    EXPECT_EQ(response[RESULT_FIELD][id]["name"], films[id]["name"]);
    EXPECT_EQ(response[RESULT_FIELD][id]["creator"], films[id]["creator"]);
    EXPECT_EQ(response[RESULT_FIELD][id]["current_film"], films[id]["current_film"]);
}

TEST_F(FilmsTableTest, getFilmInfoNotExist)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();
    size_t id = 10;

    json response = table.getFilmInfo(id);

    EXPECT_EQ(response[STATUS_FIELD], ERROR_STATUS);
}
