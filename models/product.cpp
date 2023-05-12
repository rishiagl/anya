#include "product.hpp"

using namespace models::product;

std::vector<attributes> models::product::get()
{
    auto db = models::getDBClient();
    std::vector<attributes> att_arr;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.product");
        for (auto row : result)
        {
            attributes att{};
            att.pid = row["pid"].as<int>();
            att.sid = row["sid"].as<std::string>();
            att.name = row["name"].as<std::string>();
            att.brand_sid = row["brand_sid"].as<std::string>();
            att.category_sid = row["category_sid"].as<std::string>();
            att.tax_class_code = row["tax_class_code"].as<std::string>();
            att.type_of_supply = row["type_of_supply"].as<std::string>();
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

std::string models::product::add(attributes att)
{
    auto db = models::getDBClient();
    std::string sid;
    try
    {
        auto result = db->execSqlSync("INSERT INTO anya.product(name, brand_sid, category_sid, tax_class_code, type_of_supply) VALUES($1, $2, $3, $4, $5) RETURNING sid", att.name, att.brand_sid, att.category_sid, att.tax_class_code, att.type_of_supply);
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

attributes models::product::get(std::string sid)
{
    auto db = models::getDBClient();
    attributes att{};
    att.sid = sid;
    try
    {
        auto result = db->execSqlSync("SELECT * FROM anya.product WHERE sid=$1 ", sid);
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.name = row["name"].as<std::string>();
            att.brand_sid = row["brand_sid"].as<std::string>();
            att.category_sid = row["category_sid"].as<std::string>();
            att.tax_class_code = row["tax_class_code"].as<std::string>();
            att.type_of_supply = row["type_of_supply"].as<std::string>();
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return att;
}

void models::product::update(attributes att, std::string sid)
{
    auto db = models::getDBClient();
    try
    {
        db->execSqlSync("UPDATE anya.product SET name=$1, brand_sid=$2, category_sid=$3, tax_class_code=$4, type_of_supply=$5 WHERE sid=$6", att.name, att.brand_sid, att.category_sid, att.tax_class_code, att.type_of_supply, sid);
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
    }
    return;
}

void models::product::remove(std::string sid)
{
    auto db = models::getDBClient();
    db->execSqlAsync(
        "DELETE FROM anya.product where sid=$1",
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