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
    // инициация прослушивания входящих сообщений
    void startAccept();
    // в ответ на установленное соединение - создание нового VideoStream для клиента
    void handleAccept(const boost::system::error_code& error);

    // чтение данных с клиента
    void startRead();
    // обработка полученных данных
    void handleRead(const boost::system::error_code& error, size_t bytes_transferred);

    // запись данных на клиента
    void startWrite();
    void handleWrite(const boost::system::error_code& error);

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
