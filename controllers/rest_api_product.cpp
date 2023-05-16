#include "rest_api_product.hpp"
#include "../database/database.hpp"
#include <string>
#include <vector>

using namespace rest::api;

void product::get(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto db = database::getDBClient();
    auto resp = HttpResponse::newHttpResponse();
    db->execSqlAsync(
        "SELECT * FROM anya.product", [&resp](const drogon::orm::Result &result)
        {
        std::vector<entity::product> att_arr;
        for (auto row : result)
        {
            entity::product att{};
            att.pid = row["pid"].as<int>();
            att.sid = row["sid"].as<std::string>();
            att.name = row["name"].as<std::string>();
            att.brand_sid = row["brand_sid"].as<std::string>();
            att.category_sid = row["category_sid"].as<std::string>();
            att.tax_class_code = row["tax_class_code"].as<std::string>();
            att.type_of_supply = row["type_of_supply"].as<std::string>();
            att_arr.push_back(att);
        }
        std::string buffer = glz::write_json(att_arr);
            resp->setStatusCode(k200OK);
            resp->setContentTypeCode(CT_APPLICATION_JSON);
            resp->setBody(buffer); },
        [&resp](const drogon::orm::DrogonDbException &e)
        {
            LOG_DEBUG << "ERROR CATCHED";
            std::cerr << "error:" << e.base().what() << std::endl;
            resp->setStatusCode(k500InternalServerError);
            resp->setContentTypeCode(CT_TEXT_PLAIN);
            resp->setBody(e.base().what());
        });
    callback(resp);
}

void product::create(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();
    entity::product att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
        att.brand_sid = (*json)["brand_sid"].asString();
        att.category_sid = (*json)["category_sid"].asString();
        att.tax_class_code = (*json)["tax_class_code"].asString();
        att.type_of_supply = (*json)["type_of_supply"].asString();
    }
    auto db = database::getDBClient();
    db->execSqlAsync(
        "INSERT INTO anya.product(name, brand_sid, category_sid, tax_class_code, type_of_supply) VALUES($1, $2, $3, $4, $5) RETURNING sid",
        [&resp](const drogon::orm::Result &result)
        {
            std::string sid;
            for (auto row : result)
            {
                sid = row["sid"].as<std::string>();
            }
            std::string msg_suc = "inserted Succesfully \n product ID: " + sid;
            resp->setStatusCode(k200OK);
            resp->setContentTypeCode(CT_TEXT_PLAIN);
            resp->setBody(msg_suc);
        },
        [&resp](const drogon::orm::DrogonDbException &e)
        {
            LOG_DEBUG << "ERROR CATCHED";
            std::cerr << "error:" << e.base().what() << std::endl;
            resp->setStatusCode(k422UnprocessableEntity);
            resp->setContentTypeCode(CT_TEXT_PLAIN);
            resp->setBody(e.base().what());
        },
        att.name, att.brand_sid, att.category_sid, att.tax_class_code, att.type_of_supply);
    callback(resp);
}

void product::getOne(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string &&sid)
{
    auto resp = HttpResponse::newHttpResponse();
    LOG_DEBUG << "product id given " << sid;
    auto db = database::getDBClient();
    db->execSqlAsync(
        "SELECT * FROM anya.product WHERE sid=$1 ",
        [&resp, sid](const drogon::orm::Result &result)
        {
            entity::product att{};
            att.sid = sid;
            for (auto row : result)
            {
                att.pid = row["pid"].as<int>();
                att.name = row["name"].as<std::string>();
                att.brand_sid = row["brand_sid"].as<std::string>();
                att.category_sid = row["category_sid"].as<std::string>();
                att.tax_class_code = row["tax_class_code"].as<std::string>();
                att.type_of_supply = row["type_of_supply"].as<std::string>();
            }
            std::string buffer = glz::write_json(att);
            resp->setStatusCode(k200OK);
            resp->setContentTypeCode(CT_APPLICATION_JSON);
            resp->setBody(buffer);
        },
        [&resp](const drogon::orm::DrogonDbException &e)
        {
            LOG_DEBUG << "ERROR CATCHED";
            std::cerr << "error:" << e.base().what() << std::endl;
            resp->setStatusCode(k500InternalServerError);
            resp->setContentTypeCode(CT_TEXT_PLAIN);
            resp->setBody(e.base().what());
        },
        sid);
    callback(resp);
}

void product::updateOne(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback,
                        std::string &&sid)
{
    auto resp = HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();
    entity::product att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
        att.brand_sid = (*json)["brand_sid"].asString();
        att.category_sid = (*json)["category_sid"].asString();
        att.tax_class_code = (*json)["tax_class_code"].asString();
        att.type_of_supply = (*json)["type_of_supply"].asString();
    }
    auto db = database::getDBClient();
    db->execSqlAsync(
        "UPDATE anya.product SET name=$1, brand_sid=$2, category_sid=$3, tax_class_code=$4, type_of_supply=$5 WHERE sid=$6",
        [&resp](const drogon::orm::Result &result)
        {
            std::string msg_suc = "Updated Succesfully";
            resp->setStatusCode(k200OK);
            resp->setContentTypeCode(CT_TEXT_PLAIN);
            resp->setBody(msg_suc);
        },
        [&resp](const drogon::orm::DrogonDbException &e)
        {
            LOG_DEBUG << "ERROR CATCHED";
            std::cerr << "error:" << e.base().what() << std::endl;
            resp->setStatusCode(k422UnprocessableEntity);
            resp->setContentTypeCode(CT_TEXT_PLAIN);
            resp->setBody(e.base().what());
        },
        att.name, att.brand_sid, att.category_sid, att.tax_class_code, att.type_of_supply, sid);
    callback(resp);
}

void product::deleteOne(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback,
                        std::string &&sid)
{
    auto resp = HttpResponse::newHttpResponse();
    auto db = database::getDBClient();
    db->execSqlAsync(
        "DELETE FROM anya.product where sid=$1",
        [&resp](const drogon::orm::Result &result)
        {
            LOG_DEBUG << result.affectedRows();
            std::string msg_suc = "Deleted Succesfully";
            resp->setStatusCode(k200OK);
            resp->setContentTypeCode(CT_TEXT_PLAIN);
            resp->setBody(msg_suc);
        },
        [&resp](const drogon::orm::DrogonDbException &e)
        {
            std::cerr << "error:" << e.base().what() << std::endl;
            resp->setStatusCode(k500InternalServerError);
            resp->setContentTypeCode(CT_TEXT_PLAIN);
            resp->setBody(e.base().what());
        },
        sid);
    callback(resp);
}
