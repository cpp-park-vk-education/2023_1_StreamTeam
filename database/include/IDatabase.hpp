#pragma once

#include <string>

#include "json.hpp"
#include "constants.hpp"

using json = nlohmann::json;

class IDatabase
{
public:
    virtual json createTable(json) = 0;
    virtual json dropTable(std::string) = 0;
    virtual json select(json) = 0;
    virtual json insert(json) = 0;
    virtual json remove(json) = 0;
    virtual json update(json) = 0;

    virtual ~IDatabase() = default;
};
