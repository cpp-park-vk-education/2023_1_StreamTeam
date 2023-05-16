#pragma once

#include <iostream>
#include <memory>
#include <pqxx/pqxx>
#include <string>

#include "IDatabase.hpp"
#include "PostgreConnection.hpp"

class PostgreSQL : public IDatabase
{
public:
    PostgreSQL() = default;
    PostgreSQL(std::shared_ptr<PostgreConnection> _connectionParams);

    json createTable(json) override;
    json dropTable(std::string) override;
    json update(json) override;
    json insert(json) override;
    json select(json) override;
    json remove(json) override;

    ~PostgreSQL() = default;

private:
    std::shared_ptr<PostgreConnection> connectionParams;
    std::shared_ptr<pqxx::connection> connection;
};
