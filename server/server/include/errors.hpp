#pragma once

#include <stdexcept>
#include <string>

class Error : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class AcceptError : public Error {
public:
    using Error::Error;
};

class WrongPortError : public Error {
public:
    using Error::Error;
};

class BadSessionError : public Error {
public:
    using Error::Error;
};