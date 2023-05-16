#include <gtest/gtest.h>
#include <string>
#include "server.hpp"
#include "errors.hpp"

using ioc = boost::asio::io_context;

TEST(ServerTest, ServicePort) {
    ioc io_context;
    EXPECT_THROW(Server server(io_context, 1000), WrongPortError);
}
