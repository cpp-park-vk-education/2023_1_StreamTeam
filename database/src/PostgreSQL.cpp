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

    std::string query = "SELECT ";

    for (size_t i = 0; i < request["SELECT"].size(); ++i)
    {
        query += request["SELECT"][i].get<std::string>();

        if (i != request["SELECT"].size() - 1)
        {
            query += ", ";
        }
    }

    query += " FROM ";

    for (size_t i = 0; i < request["FROM"].size(); ++i)
    {
        query += request["FROM"][i].get<std::string>();

        if (i != request["FROM"].size() - 1)
        {
            query += ", ";
        }
    }

    if (request["WHERE"].size() > 0)
    {
        query += " WHERE ";
    }

    for (size_t i = 0; i < request["WHERE"].size(); ++i)
    {
        query += request["WHERE"][i].get<std::string>();

        if (i != request["WHERE"].size() - 1)
        {
            query += " AND ";
        }
    }

    try
    {
        pqxx::work worker(*connection);
        pqxx::result result = worker.exec(query);
        worker.commit();
        response["result"] = {};

        for (auto row = result.begin(); row != result.end(); ++row)
        {
            json item;

            for (auto field = row->begin(); field != row->end(); ++field)
            {
                if (field.is_null())
                {
                    item[field.name()] = nullptr;
                    continue;
                }

                switch (field->type())
                {
                case pqxx::oid{BIGINT}:
                case pqxx::oid{SMALLINT}:
                case pqxx::oid{INT}:
                    item[field.name()] = field.as<int>();
                    break;
                case pqxx::oid{BOOLEAN}:
                    item[field.name()] = field.as<bool>();
                    break;
                case pqxx::oid{JSONB}:
                    item[field.name()] = json::parse(field.as<std::string>().c_str());
                    break;
                default:
                    item[field.name()] = field.as<std::string>().c_str();
                    break;
                }
            }
            response["result"].push_back(item);
        }

        if (response["result"].empty() || (response["result"][0].contains("sum") && response["result"][0]["sum"].empty()))
        {
            response[STATUS_FIELD] = ERROR_STATUS;
            response["msg"] = "No records with such search terms.";
        }
    }
    catch (std::exception const &e)
    {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = "PostgreSQL::select: " + std::string(e.what());
    }

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
