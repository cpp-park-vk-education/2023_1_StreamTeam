#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

#include "video_stream.hpp"

using boost::asio::ip::tcp;

class VideoServer {
public:
    VideoServer(boost::asio::io_context& io_context, const std::string& address, unsigned short port);

    void start();
    void stop();
private:

    void start_accept();
    void handle_accept(const boost::system::error_code& error);

    void start_read();
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

    void start_write();
    void handle_write(const boost::system::error_code& error);

    boost::asio::io_context& io_context;
    tcp::acceptor acceptor;
    tcp::socket socket;
    boost::asio::signal_set signals;

    std::vector<std::unique_ptr<VideoStream>> streams;
    SwsContext* sws_context;
    uint8_t* buffer;
    int buffer_size;

    bool streaming;
};
