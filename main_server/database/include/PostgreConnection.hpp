#pragma once

#include <iostream>
#include <string>
#include <map>

#include <libconfig.h++>

#include "constants.hpp"

using libconfig::Config;

class PostgreConnection
{
public:
    PostgreConnection(std::string config_path);

    PostgreConnection(std::string dbname, std::string user, std::string password = "postgres",
                      std::string host = "127.0.0.1", std::string hostaddr = "", std::string port = "5432");

    std::map<std::string, std::string> reformat() const;

private:
    std::string dbname;
    std::string user;
    std::string password;
    std::string host;
    std::string hostaddr;
    std::string port;
};
