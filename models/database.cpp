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

std::string models::getCompanyIdbyId(int id)
{
    std::string cid;
    try
    {
        auto result = pgclient->execSqlSync("SELECT company_id FROM anya.company WHERE id=$1 ", id);
        for (auto row : result)
        {
            cid = row["company_id"].as<std::string>();
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return cid;
}
