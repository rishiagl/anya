#include "brand.hpp"

using namespace models::brand;

std::vector<attributes> models::brand::get()
{
    auto db = models::getDBClient();
    std::vector<attributes> att_arr;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.brand");
        for (auto row : result)
        {
            attributes att{};
            att.pid = row["pid"].as<int>();
            att.sid = row["sid"].as<std::string>();
            att.name = row["name"].as<std::string>();
            att.company_sid = row["company_sid"].as<std::string>();
            att_arr.push_back(att);
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return att_arr;
}

std::string models::brand::add(attributes att)
{
    auto db = models::getDBClient();
    std::string sid;
    try
    {
        auto result = db->execSqlSync("INSERT INTO anya.brand(name, company_sid) VALUES($1, $2) RETURNING sid", att.name, att.company_sid);
        for (auto row : result)
        {
            sid = row["sid"].as<std::string>();
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return sid;
}

attributes models::brand::get(std::string sid)
{
    auto db = models::getDBClient();
    attributes att{};
    att.sid = sid;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.brand WHERE sid=$1 ", sid);
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.name = row["name"].as<std::string>();
            att.company_sid = row["company_sid"].as<std::string>();
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return att;
}

void models::brand::update(attributes att, std::string sid)
{
    auto db = models::getDBClient();
    try
    {
        db->execSqlSync("UPDATE anya.brand SET name=$1, company_sid=$2 WHERE sid=$3", att.name, att.company_sid, sid);
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return;
}

void models::brand::remove(std::string sid)
{
    auto db = models::getDBClient();
    db->execSqlAsync(
        "DELETE FROM anya.brand where sid=$1",
        [](const drogon::orm::Result &result)
        {
            LOG_DEBUG << result.affectedRows();
        },
        [](const drogon::orm::DrogonDbException &e)
        {
            std::cerr << "error:" << e.base().what() << std::endl;
        },
        sid);
    return;
}