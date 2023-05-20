#include "message.hpp"

#include <cstring>
#include <iomanip>
#include <sstream>

Message::Message() : body_length_(0) {}

Message::Message(const std::string& msg) {
    store_body(msg);
    encode_header();
}

const std::array<char, Message::header_length + Message::max_body_length>& Message::data() const {
    return data_;
}
std::array<char, Message::header_length + Message::max_body_length>& Message::data() {
    return data_;
}
std::size_t Message::length() const { return header_length + body_length_; }

const char* Message::body() const { return data_.data() + header_length; }

char* Message::body() { return data_.data() + header_length; }

std::size_t Message::body_length() const { return body_length_; }

bool Message::decode_header() {
    std::array<char, header_length + 1> header = {};
    std::strncat(header.data(), data_.data(), header_length);
    body_length_ = std::atoi(header.data());
    if (body_length_ > max_body_length) {
        body_length_ = 0;
        return false;
    }
    return true;
}

void Message::store_body(const std::string& msg) {
    body_length_ = msg.length();
    std::memcpy(body(), msg.c_str(), body_length_);
}
void Message::encode_header() {
    std::array<char, header_length + 1> header = {};
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << body_length_;
    std::strcat(header.data(), oss.str().c_str());
    std::memcpy(data_.data(), header.data(), header_length);
}
