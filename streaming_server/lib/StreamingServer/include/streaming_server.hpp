#pragma once

#include <boost/asio.hpp>
#include <thread>

class BasicServer {
public:
    virtual ~BasicServer() = 0;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool is_running() const = 0;
    virtual unsigned short get_port() const = 0;
};

class StreamingServer : BasicServer {
public:
    StreamingServer(unsigned short port = 8080);
    ~StreamingServer() override;
    void start() override;
    void stop() override;

    bool is_running() const override;
    unsigned short get_port() const override;
private:
    void handleRequest(boost::asio::ip::tcp::socket& socket);
    void acceptConnections();

    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::ip::tcp::socket socket_;
    unsigned short port_;
    bool is_running_;
};