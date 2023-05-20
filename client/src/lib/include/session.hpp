#pragma once

#include <boost/asio.hpp>
#include <list>
#include <iostream>
#include <memory>
#include "request.hpp"

using boost::asio::ip::tcp;

class Session {
public:
    Session(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints);

    void Send(const std::string& msg);
    void Close();
    static std::shared_ptr<Session> getInstance();
    static void setInstance(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints);

private:

    inline static std::shared_ptr<Session> session_instance_ = nullptr;
    void Connect(const tcp::resolver::results_type& endpoint);
    void ReadHeader();
    void ReadBody();
    void Write();

    boost::asio::io_context& io_context_;
    tcp::socket socket_;
    Request read_msg_;
    std::list<Request> queue_;
};
