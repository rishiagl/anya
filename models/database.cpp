#include "database.hpp"

drogon::orm::DbClientPtr pgclient;
void models::storeDBClient(drogon::orm::DbClientPtr &dbclient)
{
    pgclient = dbclient;
}

drogon::orm::DbClientPtr models::getDBClient()
{
    return pgclient;
}
