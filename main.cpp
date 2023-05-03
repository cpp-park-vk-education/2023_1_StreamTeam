#include <iostream>
#include <string>

#include "PostgreSQL.hpp"
#include "UsersTable.hpp"

std::string CONFIG_PATH = "db_config.cfg";

int main(int argc, char **argv)
{
    std::shared_ptr<PostgreConnection> postgresParams = std::make_shared<PostgreConnection>(CONFIG_PATH);
    std::shared_ptr<PostgreSQL> postgres = std::make_shared<PostgreSQL>(postgresParams);

    UsersTable usersTable(postgres);

    std::cout << usersTable.checkUser(2);

    return 0;
}
