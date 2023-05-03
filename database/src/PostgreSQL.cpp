#include "PostgreSQL.hpp"

PostgreSQL::PostgreSQL(std::shared_ptr<PostgreConnection> _connectionParams)
{
    connectionParams = _connectionParams;

    try
    {
        std::map<std::string, std::string> result = connectionParams->reformat();
        std::string status = result[STATUS_FIELD];
        std::string parameters = result[PARAMS_FIELD];
        if (status == SUCCESS_STATUS)
        {
            connection = std::make_shared<pqxx::connection>(parameters);
            if ((*connection).is_open())
            {
                std::cout << "Opened database successfully: " << (*connection).dbname() << std::endl;
            }
            else
            {
                std::cout << "Can't open database" << std::endl;
            }
        }
        else
        {
            std::cout << "Wrong parameters to connect to database" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

json PostgreSQL::createTable(json request)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    return response;
}

json PostgreSQL::dropTable(std::string)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    return response;
}

json PostgreSQL::select(json request)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    return response;
}

json PostgreSQL::insert(json request)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    return response;
}

json PostgreSQL::remove(json request)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    return response;
}

json PostgreSQL::update(json request)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    return response;
}
