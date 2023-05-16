#include "../include/streaming_server.hpp"


StreamingServer::StreamingServer(unsigned short port)
: io_context_(), acceptor_(io_context_), socket_(io_context_), port_(port), is_running_(false) {}

StreamingServer::~StreamingServer() = default;

void StreamingServer::start() {
    if (is_running_)
        return;

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port_);
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    is_running_ = true;
    acceptConnections();
    io_context_.run();
}

void StreamingServer::stop() {
    if (!is_running_)
        return;

    io_context_.stop();
    is_running_ = false;
}

bool StreamingServer::is_running() const {
    return is_running_;
}

unsigned short StreamingServer::get_port() const {
    return port_;
}

void StreamingServer::handleRequest(boost::asio::ip::tcp::socket& socket) {
    // TODO
}

void StreamingServer::acceptConnections() {
    acceptor_.async_accept(socket_, [this](const boost::system::error_code& error) {
        if (!error) {
            handleRequest(socket_);
            acceptConnections();
        }
    });
}
