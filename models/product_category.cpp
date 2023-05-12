#include "product_category.hpp"

using namespace models::product_category;

std::vector<attributes> models::product_category::get()
{
    auto db = models::getDBClient();
    std::vector<attributes> att_arr;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.product_category");
        for (auto row : result)
        {
            attributes att{};
            att.pid = row["pid"].as<int>();
            att.sid = row["sid"].as<std::string>();
            att.name = row["name"].as<std::string>();
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

std::string models::product_category::add(attributes att)
{
    auto db = models::getDBClient();
    std::string sid;
    try
    {
        auto result = db->execSqlSync("INSERT INTO anya.product_category(name) VALUES($1, $2) RETURNING sid", att.name);
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

attributes models::product_category::get(std::string sid)
{
    auto db = models::getDBClient();
    attributes att{};
    att.sid = sid;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.product_category WHERE sid=$1 ", sid);
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.name = row["name"].as<std::string>();
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return att;
}

void models::product_category::update(attributes att, std::string sid)
{
    auto db = models::getDBClient();
    try
    {
        db->execSqlSync("UPDATE anya.product_category SET name=$1 WHERE sid=$2", att.name, sid);
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return;
}

void models::product_category::remove(std::string sid)
{
    auto db = models::getDBClient();
    db->execSqlAsync(
        "DELETE FROM anya.product_category where sid=$1",
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