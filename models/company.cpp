#include "company.hpp"

using namespace models::company;

std::vector<attributes> models::company::get()
{
    auto db = models::getDBClient();
    std::vector<attributes> att_arr;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.company");
        for (auto row : result)
        {
            attributes att{};
            att.pid = row["pid"].as<int>();
            att.sid = row["sid"].as<std::string>();
            att.name = row["name"].as<std::string>();
            att.address = row["address"].as<std::string>();
            att.city = row["city"].as<std::string>();
            att.state = row["state"].as<std::string>();
            att.country = row["country"].as<std::string>();
            att.cin = row["cin"].as<std::string>();
            att.pan = row["pan"].as<std::string>();
            att.gstin = row["gstin"].as<std::string>();
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

std::string models::company::add(attributes att)
{
    auto db = models::getDBClient();
    std::string sid;
    try
    {
        auto result = db->execSqlSync("INSERT INTO anya.company(name, address, city, state, country, cin, pan, gstin) VALUES($1, $2, $3, $4, $5, $6, $7, $8) RETURNING sid", att.name, att.address, att.city, att.state, att.country, att.cin, att.pan, att.gstin);
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

attributes models::company::get(std::string sid)
{
    auto db = models::getDBClient();
    attributes att{};
    att.sid = sid;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.company WHERE sid=$1 ", sid);
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.name = row["name"].as<std::string>();
            att.address = row["address"].as<std::string>();
            att.city = row["city"].as<std::string>();
            att.state = row["state"].as<std::string>();
            att.country = row["country"].as<std::string>();
            att.cin = row["cin"].as<std::string>();
            att.pan = row["pan"].as<std::string>();
            att.gstin = row["gstin"].as<std::string>();
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return att;
}

void models::company::update(attributes att, std::string sid)
{
    auto db = models::getDBClient();
    try
    {
        db->execSqlSync("UPDATE anya.company SET name=$1, address=$2, city=$3, state=$4, country=$5, cin=$6, pan=$7, gstin=$8 WHERE sid=$9", att.name, att.address, att.city, att.state, att.country, att.cin, att.pan, att.gstin, sid);
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return;
}

void models::company::remove(std::string sid)
{
    auto db = models::getDBClient();
    db->execSqlAsync(
        "DELETE FROM anya.company where sid=$1",
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