#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include "session.hpp"
#include "iroom.hpp"
#include "router.hpp"

class ISession;
using session_ptr = std::shared_ptr<ISession>;


struct GMockRoom : public IRoom {
    MOCK_METHOD(void, Join, (session_ptr participant), (override));
    MOCK_METHOD(void, Leave, (session_ptr participant), (override));
    MOCK_METHOD(void, Send, (const std::string& msg), (override));
};

TEST(SessionTest, JoinTest) {
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor acceptor(io_context);
    boost::asio::ip::tcp::socket socket(io_context);
    acceptor.accept(socket);
    auto room = std::make_shared<GMockRoom>();
    auto rout = std::make_shared<Router>();
    auto session = std::make_shared<Session>(std::move(socket), room, rout);
    EXPECT_CALL(*room, Join(::testing::An<session_ptr>()));
    session->Run();
}
