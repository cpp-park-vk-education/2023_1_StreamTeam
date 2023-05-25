#pragma once

#include <array>
#include <list>
#include <string>

class Message {
   public:
    static constexpr std::size_t header_length = 4;
    static constexpr std::size_t max_body_length = 16384;

    Message();
    Message(const std::string& msg);
    const std::array<char, header_length + max_body_length>& data() const;
    std::array<char, header_length + max_body_length>& data();
    std::size_t length() const;
    const char* body() const;
    char* body();
    std::size_t body_length() const;
    bool decode_header();

   private:
    void store_body(const std::string& msg);
    void encode_header();
    std::array<char, header_length + max_body_length> data_;
    std::size_t body_length_;
};
