#include "company.hpp"

using namespace models::company;

attributes models::company::get(int id)
{
    drogon::orm::DbClientPtr db = models::getDBClient();
    attributes c_att{};
    c_att.id = id;
    std::string cid;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.company WHERE id=$1 ", id);
        for (auto row : result)
        {
            c_att.company_id = row["company_id"].as<std::string>();
            c_att.name = row["name"].as<std::string>();
            c_att.address = row["address"].as<std::string>();
            c_att.city = row["city"].as<std::string>();
            c_att.state = row["state"].as<std::string>();
            c_att.country = row["country"].as<std::string>();
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return c_att;
}

// attributes get(int id)
// {
//     drogon::orm::DbClientPtr db = models::getDBClient();
//     attributes c_att{};
//     c_att.id = id;
//     std::string cid;
//     try
//     {
//         auto result = db->execSqlSync("SELECT * FROM anya.company WHERE id=$1 ", id);
//         for (auto row : result)
//         {
//             c_att.company_id = row["company_id"].as<std::string>();
//             c_att.name = row["name"].as<std::string>();
//             c_att.address = row["address"].as<std::string>();
//             c_att.city = row["city"].as<std::string>();
//             c_att.state = row["state"].as<std::string>();
//             c_att.country = row["country"].as<std::string>();
//         }
//     }
//     catch (const drogon::orm::DrogonDbException &e)
//     {
//         LOG_DEBUG << "ERROR CATCHED";
//         std::cerr << "error:" << e.base().what() << std::endl;
//     }
//     return c_att;
// }