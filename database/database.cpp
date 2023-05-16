#include "database.hpp"

drogon::orm::DbClientPtr pgclient;
void database::storeDBClient(drogon::orm::DbClientPtr &dbclient)
{
    pgclient = dbclient;
}

drogon::orm::DbClientPtr database::getDBClient()
{
    return pgclient;
}
