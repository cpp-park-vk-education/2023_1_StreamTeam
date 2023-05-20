#include "server.hpp"
#include "session.hpp"

void Server::Accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket), rooms_, database_)->Run();
            }
            Accept();
        });
}