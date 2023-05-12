#include "tax_class.hpp"

using namespace models::tax_class;

std::vector<attributes> models::tax_class::get()
{
    auto db = models::getDBClient();
    std::vector<attributes> att_arr;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.tax_class");
        for (auto row : result)
        {
            attributes att{};
            att.pid = row["pid"].as<int>();
            att.code = row["code"].as<int>();
            att.type_of_code = row["type_of_code"].as<std::string>();
            att.description = row["description"].as<std::string>();
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

int models::tax_class::add(attributes att)
{
    auto db = models::getDBClient();
    int code;
    try
    {
        auto result = db->execSqlSync("INSERT INTO anya.tax_class(code, type_of_code, description, rate) VALUES($1, $2, $3, $4) RETURNING code", att.code, att.type_of_code, att.description, att.rate);
        for (auto row : result)
        {
            code = row["code"].as<int>();
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return code;
}

attributes models::tax_class::get(int code)
{
    auto db = models::getDBClient();
    attributes att{};
    att.code = code;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.tax_class WHERE code=$1 ", code);
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.type_of_code = row["type_of_code"].as<std::string>();
            att.description = row["description"].as<std::string>();
            att.rate = row["row"].as<int>();
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return att;
}

void models::tax_class::update(attributes att, int code)
{
    auto db = models::getDBClient();
    try
    {
        db->execSqlSync("UPDATE anya.tax_class SET type_of_code=$1, description=$2, rate=$3 WHERE code=$4", att.type_of_code, att.description, att.rate, code);
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return;
}

void models::tax_class::remove(int code)
{
    auto db = models::getDBClient();
    db->execSqlAsync(
        "DELETE FROM anya.tax_class where code=$1",
        [](const drogon::orm::Result &result)
        {
            LOG_DEBUG << result.affectedRows();
        },
        [](const drogon::orm::DrogonDbException &e)
        {
            std::cerr << "error:" << e.base().what() << std::endl;
        },
        code);
    return;
}