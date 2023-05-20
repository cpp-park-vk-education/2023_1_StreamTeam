#include <iostream>
#include <thread>
#include <vector>
#include <pqxx>

#include "../client/src/lib/include/session.hpp"

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(argv[1], argv[2]);
        Client c(io_context, endpoints);

        std::thread t([&io_context]() {
            io_context.run();
        });

       std::string line;
       while (std::getline(std::cin, line)) {
               c.Send(line);
           }
       c.Close();
       t.join();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
    // t.join();
    return 0;
}
