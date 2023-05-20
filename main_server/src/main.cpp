#include <iostream>

#include "PostgreSQL.hpp"
#include "server.hpp"

using boost::asio::ip::tcp;
std::string CONFIG_PATH = "config.cfg";

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: chat_server <port>\n";
            return EXIT_FAILURE;
        }
        boost::asio::io_context io_context;
        std::shared_ptr<PostgreConnection> postgresParams =
            std::make_shared<PostgreConnection>(CONFIG_PATH);
        std::shared_ptr<PostgreSQL> postgres =
            std::make_shared<PostgreSQL>(postgresParams);
        Server server(io_context, std::atoi(argv[1]),
                      postgres);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}