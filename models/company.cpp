#include "company.hpp"
#include <vector>

using namespace models::company;

std::vector<attributes> models::company::get()
{
    drogon::orm::DbClientPtr db = models::getDBClient();
    std::vector<attributes> c_att_arr;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.company");
        for (auto row : result)
        {
            attributes c_att{};
            c_att.id = row["id"].as<int>();
            c_att.company_id = row["company_id"].as<std::string>();
            c_att.name = row["name"].as<std::string>();
            c_att.address = row["address"].as<std::string>();
            c_att.city = row["city"].as<std::string>();
            c_att.state = row["state"].as<std::string>();
            c_att.country = row["country"].as<std::string>();
            c_att_arr.push_back(c_att);
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return c_att_arr;
}

std::string models::company::add(attributes c_att)
{
    drogon::orm::DbClientPtr db = models::getDBClient();
    std::string cid;
    try
    {
        auto result = db->execSqlSync("INSERT INTO anya.company(name, address, city, state, country) VALUES($1, $2, $3, $4, $5) RETURNING company_id", c_att.name, c_att.address, c_att.city, c_att.state, c_att.country);
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

attributes models::company::get(std::string cid)
{
    drogon::orm::DbClientPtr db = models::getDBClient();
    attributes c_att{};
    c_att.company_id = cid;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.company WHERE company_id=$1 ", cid);
        for (auto row : result)
        {
            c_att.id = row["id"].as<int>();
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