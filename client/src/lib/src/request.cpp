#include "../include/request.hpp"

#include <cstring>
#include <iomanip>
#include <sstream>

Request::Request() : body_length_(0) {}

Request::Request(const std::string& msg) {
    store_body(msg);
    encode_header();
}

const std::array<char, Request::header_length + Request::max_body_length>& Request::data() const {
    return data_;
}
std::array<char, Request::header_length + Request::max_body_length>& Request::data() {
    return data_;
}
std::size_t Request::length() const { return header_length + body_length_; }

const char* Request::body() const { return data_.data() + header_length; }

char* Request::body() { return data_.data() + header_length; }

std::size_t Request::body_length() const { return body_length_; }

bool Request::decode_header() {
    std::array<char, header_length + 1> header = {};
    std::strncat(header.data(), data_.data(), header_length);
    body_length_ = std::atoi(header.data());
    if (body_length_ > max_body_length) {
        body_length_ = 0;
        return false;
    }
    return true;
}

void Request::store_body(const std::string& msg) {
    body_length_ = msg.length();
    std::memcpy(body(), msg.c_str(), body_length_);
}
void Request::encode_header() {
    std::array<char, header_length + 1> header = {};
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << body_length_;
    std::strcat(header.data(), oss.str().c_str());
    std::memcpy(data_.data(), header.data(), header_length);
}
