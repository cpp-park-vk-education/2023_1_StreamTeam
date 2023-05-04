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
    json users = UsersTableTest::getUsers();
    size_t id = users.size();

    json request = {{"username", "test1"}, {"email", "test1@mail.ru"}, {"password", "test1"}};
    json response = table.addUser(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["user"]["id"], id);
    EXPECT_EQ(response["user"]["username"], request["username"]);
    EXPECT_EQ(response["user"]["email"], request["email"]);
    EXPECT_EQ(response["user"]["password"], request["password"]);
}

TEST_F(UsersTableTest, addUserExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    json request = {{"username", "lexus"}, {"email", "lexus@mail.ru"}, {"password", "lexus"}};
    json response = table.addUser(request);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(UsersTableTest, deleteUserExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    json response = table.deleteUser(0);

    EXPECT_EQ(response["status"], "ok");
}

TEST_F(UsersTableTest, deleteUserNotExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    json response = table.deleteUser(10);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(UsersTableTest, updateUserExist)
{
    UsersTable table = UsersTableTest::getUsersTable();
    json users = UsersTableTest::getUsers();
    size_t id = 0;

    json request = {{"id", id}, {"username", "test1"}, {"email", "test1@mail.ru"}, {"password", "test1"}};
    json response = table.updateUser(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["user"]["id"], id);
    EXPECT_EQ(response["user"]["username"], request["username"]);
    EXPECT_EQ(response["user"]["email"], request["email"]);
    EXPECT_EQ(response["user"]["password"], request["password"]);
}

TEST_F(UsersTableTest, updateUserNotExist)
{
    UsersTable table = UsersTableTest::getUsersTable();
    size_t id = 10;

    json request = {{"id", id}, {"username", "test1"}, {"email", "test1@mail.ru"}, {"password", "test1"}};
    json response = table.updateUser(request);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(UsersTableTest, checkUserByIDExist)
{
    UsersTable table = UsersTableTest::getUsersTable();

    bool response = table.checkUserByID(0);

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

    json response = table.getUserInfo(id);

    json users = UsersTableTest::getUsers();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["user"]["id"], id);
    EXPECT_EQ(response["user"]["username"], users[id]["username"]);
    EXPECT_EQ(response["user"]["email"], users[id]["email"]);
    EXPECT_EQ(response["user"]["password"], users[id]["password"]);
}

TEST_F(UsersTableTest, getUserInfoNotExist)
{
    UsersTable table = UsersTableTest::getUsersTable();
    size_t id = 10;

    json response = table.getUserInfo(id);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(RoomsTableTest, addRoom)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    json rooms = RoomsTableTest::getRooms();

    json request = {{"name", "test"}, {"creator", 0}};
    json response = table.addRoom(request);

    size_t id = rooms.size();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["room"]["id"], id);
    EXPECT_EQ(response["room"]["name"], request["name"]);
    EXPECT_EQ(response["room"]["creator"], request["creator"]);
}

TEST_F(RoomsTableTest, deleteRoomExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    json response = table.deleteRoom(0);

    EXPECT_EQ(response["status"], "ok");
}

TEST_F(RoomsTableTest, deleteRoomNotExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    json response = table.deleteRoom(10);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(RoomsTableTest, updateRoomExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    json rooms = RoomsTableTest::getRooms();
    size_t id = 0;

    json request = {{"id", id}, {"name", "test"}, {"creator", "2"}};
    json response = table.updateRoom(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["room"]["id"], id);
    EXPECT_EQ(response["room"]["name"], request["name"]);
    EXPECT_EQ(response["room"]["creator"], request["creator"]);
}

TEST_F(RoomsTableTest, updateRoomNotExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    size_t id = 10;

    json request = {{"id", id}, {"name", "test"}, {"creator", "2"}};
    json response = table.updateRoom(request);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(RoomsTableTest, checkRoomExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    bool response = table.checkRoom(0);

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

    json response = table.getRoomInfo(id);

    json rooms = RoomsTableTest::getRooms();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["room"]["id"], id);
    EXPECT_EQ(response["room"]["name"], rooms[id]["name"]);
    EXPECT_EQ(response["room"]["creator"], rooms[id]["creator"]);
    EXPECT_EQ(response["room"]["current_film"], rooms[id]["current_film"]);
}

TEST_F(RoomsTableTest, getRoomInfoNotExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    size_t id = 10;

    json response = table.getRoomInfo(id);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(RoomsTableTest, getAllRooms)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();

    json response = table.getAllRooms();

    json rooms = RoomsTableTest::getRooms();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["rooms"].size(), rooms.size());
}

TEST_F(RoomsTableTest, getCurrentFilmExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    size_t id = 0;

    json response = table.getCurrentFilm(id);

    json rooms = RoomsTableTest::getRooms();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["room"]["current_film"], rooms[id]["current_film"]);
}

TEST_F(RoomsTableTest, getCurrentFilmNotExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    size_t id = 10;

    json response = table.getCurrentFilm(id);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(RoomsTableTest, checkCurrentFilmExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    size_t id = 0;

    json response = table.checkCurrentFilm(id);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response, true);
}

TEST_F(RoomsTableTest, checkCurrentFilmNotExist)
{
    RoomsTable table = RoomsTableTest::getRoomsTable();
    size_t id = 10;

    json response = table.checkCurrentFilm(id);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response, false);
}

TEST_F(ViewersTableTest, getUserRoomsExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 2;

    json response = table.getUserRooms(id);
    std::vector<int> actual_rooms{0};
    std::vector<int> actual_points{0};

    for (size_t i = 0; i < response["rooms"].size(); ++i)
    {
        actual_rooms.push_back(response["rooms"][i]["id_room"]);
        actual_points.push_back(response["rooms"][i]["points"]);
    }

    json viewers = ViewersTableTest::getViewers();
    std::vector<int> expected_rooms;
    std::vector<int> expected_points;

    for (size_t i = 0; i < viewers.size(); ++i)
    {
        if (viewers[i]["id_user"] == id)
        {
            expected_rooms.push_back(viewers[i]["id_room"]);
            expected_points.push_back(viewers[i]["points"]);
        }
    }

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(actual_rooms.size(), expected_rooms.size());
    EXPECT_EQ(actual_rooms[0], expected_rooms[0]);
    EXPECT_EQ(actual_points[0], expected_points[0]);
}

TEST_F(ViewersTableTest, getUserRoomsNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 10;

    json response = table.getUserRooms(id);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(ViewersTableTest, getRoomUsersExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 1;

    json response = table.getRoomUsers(id);
    std::vector<int> actual_users{0};
    std::vector<int> actual_points{0};

    for (size_t i = 0; i < response["users"].size(); ++i)
    {
        actual_users.push_back(response["users"][i]["id_room"]);
        actual_points.push_back(response["users"][i]["points"]);
    }

    json viewers = ViewersTableTest::getViewers();
    std::vector<int> expected_users;
    std::vector<int> expected_points;

    for (size_t i = 0; i < viewers.size(); ++i)
    {
        if (viewers[i]["id_user"] == id)
        {
            expected_users.push_back(viewers[i]["id_user"]);
            expected_points.push_back(viewers[i]["points"]);
        }
    }

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(actual_users.size(), expected_users.size());
    EXPECT_EQ(actual_users[0], expected_users[0]);
    EXPECT_EQ(actual_points[0], expected_points[0]);
}

TEST_F(ViewersTableTest, getRoomUsersNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 10;

    json response = table.getRoomUsers(id);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(ViewersTableTest, addUserToRoomExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 1;

    json response = table.addUserToRoom(id, id);

    EXPECT_EQ(response["status"], "ok");
}

TEST_F(ViewersTableTest, addUserToRoomNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    size_t id = 10;

    json response = table.addUserToRoom(id, id);

    EXPECT_EQ(response["status"], "error");
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

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["points"], expected_points);
}

TEST_F(ViewersTableTest, getUserPointsInRoomNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    json viewers = ViewersTableTest::getViewers();
    size_t id = 10;

    json response = table.getUserPointsInRoom(id, id);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(ViewersTableTest, setUserPointsInRoomExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    json viewers = ViewersTableTest::getViewers();
    size_t id = 1;
    size_t old_points;
    size_t new_points = 1000;

    for (size_t i = 0; i < viewers.size(); ++i)
    {
        if (viewers[i]["id_user"] == id & viewers[i]["id_room"] == id)
        {
            old_points = viewers[i]["points"];
        }
    }

    json response = table.setUserPointsInRoom(id, id, new_points);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["id_user"], id);
    EXPECT_EQ(response["id_room"], id);
    EXPECT_EQ(response["old_points"], old_points);
    EXPECT_EQ(response["new_points"], new_points);
}

TEST_F(ViewersTableTest, setUserPointsInRoomNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    json viewers = ViewersTableTest::getViewers();
    size_t id = 10;
    size_t new_points = 1000;

    json response = table.setUserPointsInRoom(id, id, new_points);

    EXPECT_EQ(response["status"], "error");
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

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["role"], expected_role);
}

TEST_F(ViewersTableTest, getUserRoleInRoomNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    json viewers = ViewersTableTest::getViewers();
    size_t id = 10;

    json response = table.getUserRoleInRoom(id, id);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(ViewersTableTest, setUserRoleInRoomExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    json viewers = ViewersTableTest::getViewers();
    size_t id = 1;
    std::string old_role;
    std::string new_role = "banned";

    for (size_t i = 0; i < viewers.size(); ++i)
    {
        if (viewers[i]["id_user"] == id & viewers[i]["id_room"] == id)
        {
            old_role = viewers[i]["role"];
        }
    }

    json response = table.setUserRoleInRoom(id, id, new_role);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["id_user"], id);
    EXPECT_EQ(response["id_room"], id);
    EXPECT_EQ(response["old_role"], old_role);
    EXPECT_EQ(response["new_role"], new_role);
}

TEST_F(ViewersTableTest, setUserRoleInRoomExist_INVALID)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    json viewers = ViewersTableTest::getViewers();
    size_t id = 1;
    std::string new_role = "something";

    json response = table.setUserRoleInRoom(id, id, new_role);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(ViewersTableTest, setUserRoleInRoomNotExist)
{
    ViewersTable table = ViewersTableTest::getViewersTable();
    json viewers = ViewersTableTest::getViewers();
    size_t id = 10;
    std::string new_role = "guest";

    json response = table.setUserRoleInRoom(id, id, new_role);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(BidsTableTest, addBid)
{
    BidsTable table = BidsTableTest::getBidsTable();
    json bids = BidsTableTest::getBids();
    size_t id = bids.size();

    json request = {{"id_creator", 2}, {"id_room", 1}, {"text", "test"}, {"min_points", 10}, {"begin_time", "2023-03-12 10:10:10"}, {"lifetime", "04:30:00"}};
    json response = table.addBid(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["bid"]["id"], id);
    EXPECT_EQ(response["bid"]["id_creator"], request["id_creator"]);
    EXPECT_EQ(response["bid"]["id_room"], request["id_room"]);
    EXPECT_EQ(response["bid"]["text"], request["text"]);
    EXPECT_EQ(response["bid"]["min_points"], request["min_points"]);
    EXPECT_EQ(response["bid"]["begin_time"], request["begin_time"]);
    EXPECT_EQ(response["bid"]["lifetime"], request["lifetime"]);
}

TEST_F(BidsTableTest, deleteBidExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    json bids = BidsTableTest::getBids();

    json response = table.deleteBid(0);

    EXPECT_EQ(response["status"], "ok");
}

TEST_F(BidsTableTest, deleteBidNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    json bids = BidsTableTest::getBids();

    json response = table.deleteBid(10);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(BidsTableTest, updateBidExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    json users = BidsTableTest::getBids();
    size_t id = 0;

    json request = {{"id", id}, {"id_creator", 2}, {"id_room", 1}, {"text", "test"}, {"min_points", 10}, {"begin_time", "2023-03-12 10:10:10"}, {"lifetime", "04:30:00"}};
    json response = table.updateBid(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["bid"]["id"], id);
    EXPECT_EQ(response["bid"]["id_creator"], request["id_creator"]);
    EXPECT_EQ(response["bid"]["id_room"], request["id_room"]);
    EXPECT_EQ(response["bid"]["text"], request["text"]);
    EXPECT_EQ(response["bid"]["min_points"], request["min_points"]);
    EXPECT_EQ(response["bid"]["begin_time"], request["begin_time"]);
    EXPECT_EQ(response["bid"]["lifetime"], request["lifetime"]);
}

TEST_F(BidsTableTest, updateBidNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json request = {{"id", id}, {"id_creator", 2}, {"id_room", 1}, {"text", "test"}, {"min_points", 10}, {"begin_time", "2023-03-12 10:10:10"}, {"lifetime", "04:30:00"}};
    json response = table.updateBid(request);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(BidsTableTest, isEndedExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 1;

    json response = table.isEnded(id);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["is_ended"], true);
}

TEST_F(BidsTableTest, isEndedNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.isEnded(id);

    EXPECT_EQ(response["status"], "error");
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

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"], counter);
}

TEST_F(BidsTableTest, getVotesForNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getVotesFor(id);

    EXPECT_EQ(response["status"], "error");
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

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"], counter);
}

TEST_F(BidsTableTest, getVotesAgainstNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getVotesAgainst(id);

    EXPECT_EQ(response["status"], "error");
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

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"], counter);
}

TEST_F(BidsTableTest, getVotesCountNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getVotesCount(id);

    EXPECT_EQ(response["status"], "error");
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

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"], sum);
}

TEST_F(BidsTableTest, getPointsForNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getPointsFor(id);

    EXPECT_EQ(response["status"], "error");
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

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"], sum);
}

TEST_F(BidsTableTest, getPointsAgainstNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getPointsAgainst(id);

    EXPECT_EQ(response["status"], "error");
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

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"], sum);
}

TEST_F(BidsTableTest, getPointsCountNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getPointsSum(id);

    EXPECT_EQ(response["status"], "error");
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

    EXPECT_EQ(response["status"], "error");
    EXPECT_EQ(response["winners"].size(), winners.size());
    EXPECT_EQ(response["winners"][0], winners[0]);
}

TEST_F(BidsTableTest, getWinnersNotExist)
{
    BidsTable table = BidsTableTest::getBidsTable();
    size_t id = 10;

    json response = table.getWinners(id, true);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(VotesTableTest, addVoteNotExist)
{
    VotesTable table = VotesTableTest::getVotesTable();
    json votes = VotesTableTest::getVotes();
    size_t id = votes.size();

    json request = {{"id_bid", 2}, {"id_user", 2}, {"vote", false}, {"points", 100}};
    json response = table.addVote(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["vote"]["id"], id);
    EXPECT_EQ(response["vote"]["id_bid"], request["id_bid"]);
    EXPECT_EQ(response["vote"]["id_user"], request["id_user"]);
    EXPECT_EQ(response["vote"]["vote"], request["vote"]);
    EXPECT_EQ(response["vote"]["points"], request["points"]);
}

TEST_F(VotesTableTest, addVoteExist)
{
    VotesTable table = VotesTableTest::getVotesTable();
    size_t id = 10;

    json request = {{"id_bid", id}, {"id_user", id}, {"vote", false}, {"points", 100}};
    json response = table.addVote(request);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(VotesTableTest, deleteVoteExist)
{
    VotesTable table = VotesTableTest::getVotesTable();
    json votes = VotesTableTest::getVotes();

    json response = table.deleteVote(0);

    EXPECT_EQ(response["status"], "ok");
}

TEST_F(VotesTableTest, deleteVoteNotExist)
{
    VotesTable table = VotesTableTest::getVotesTable();
    json votes = VotesTableTest::getVotes();

    json response = table.deleteVote(10);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(VotesTableTest, updateVoteExist)
{
    VotesTable table = VotesTableTest::getVotesTable();
    json votes = VotesTableTest::getVotes();
    size_t id = 0;

    json request = {{"id", id}, {"id_bid", 1}, {"id_user", 1}, {"vote", false}, {"points", 100}};
    json response = table.updateVote(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["vote"]["id"], id);
    EXPECT_EQ(response["vote"]["id_bid"], request["id_bid"]);
    EXPECT_EQ(response["vote"]["id_user"], request["id_user"]);
    EXPECT_EQ(response["vote"]["vote"], request["vote"]);
    EXPECT_EQ(response["vote"]["points"], request["points"]);
}

TEST_F(VotesTableTest, updateVoteNotExist)
{
    VotesTable table = VotesTableTest::getVotesTable();
    size_t id = 10;

    json request = {{"id", id}, {"id_bid", 1}, {"id_user", 1}, {"vote", false}, {"points", 100}};
    json response = table.updateVote(request);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(FilmsTableTest, addFilm)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();
    json films = FilmsTableTest::getFilms();
    size_t id = films.size();

    json request = {{"name", "test"}, {"link", "https://www.test.ru/test"}, {"data", {{"description", "test"}}}};
    json response = table.addFilm(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["film"]["id"], id);
    EXPECT_EQ(response["film"]["name"], request["name"]);
    EXPECT_EQ(response["film"]["link"], request["link"]);
    EXPECT_EQ(response["film"]["data"]["description"], request["data"]["description"]);
}

TEST_F(FilmsTableTest, deleteFilmExist)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();

    json response = table.deleteFilm(0);

    EXPECT_EQ(response["status"], "ok");
}

TEST_F(FilmsTableTest, deleteFilmNotExist)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();

    json response = table.deleteFilm(10);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(FilmsTableTest, updateFilmExist)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();
    json films = FilmsTableTest::getFilms();
    size_t id = 0;

    json request = {{"id", id}, {"name", "test"}, {"link", "https://www.test.ru/test"}, {"data", {{"description", "test"}}}};
    json response = table.updateFilm(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["film"]["id"], id);
    EXPECT_EQ(response["film"]["name"], request["name"]);
    EXPECT_EQ(response["film"]["link"], request["link"]);
    EXPECT_EQ(response["film"]["data"]["description"], request["data"]["description"]);
}

TEST_F(FilmsTableTest, updateFilmNotExist)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();
    size_t id = 10;

    json request = {{"id", id}, {"name", "test"}, {"link", "https://www.test.ru/test"}, {"data", {{"description", "test"}}}};
    json response = table.updateFilm(request);

    EXPECT_EQ(response["status"], "error");
}

TEST_F(FilmsTableTest, getFilmInfoExist)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();
    size_t id = 0;

    json response = table.getFilmInfo(id);

    json films = FilmsTableTest::getFilms();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["film"]["id"], id);
    EXPECT_EQ(response["film"]["name"], films[id]["name"]);
    EXPECT_EQ(response["film"]["creator"], films[id]["creator"]);
    EXPECT_EQ(response["film"]["current_film"], films[id]["current_film"]);
}

TEST_F(FilmsTableTest, getFilmInfoNotExist)
{
    FilmsTable table = FilmsTableTest::getFilmsTable();
    size_t id = 10;

    json response = table.getFilmInfo(id);

    EXPECT_EQ(response["status"], "error");
}
