#include <dblib/database.hpp>

drogon::orm::DbClientPtr pgclient;
void dblib::storeDBClient(drogon::orm::DbClientPtr& dbclient)
{
    pgclient = dbclient;
}

drogon::orm::DbClientPtr dblib::getDBClient()
{
    return pgclient;
}

std::string dblib::getCompanyIdbyId(int id)
{
    std::string cid;
    try
    {
        auto result = pgclient->execSqlSync("SELECT shop_id FROM anya.company WHERE id=$1 ", id);
        for (auto row : result)
        {
            cid = row["shop_id"].as<std::string>();
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return cid;
}
