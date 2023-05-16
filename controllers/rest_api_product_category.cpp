#include "rest_api_product_category.hpp"
#include "../database/database.hpp"
#include <string>
#include <vector>

using namespace rest::api;

void product_category::get(const HttpRequestPtr &req,
                           std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto db = database::getDBClient();
    auto resp = HttpResponse::newHttpResponse();
    db->execSqlAsync(
        "SELECT * FROM anya.product_category", [&resp](const drogon::orm::Result &result)
        {
            std::vector<entity::product_category> att_arr;
        for (auto row : result)
        {
            entity::product_category att{};
            att.pid = row["pid"].as<int>();
            att.sid = row["sid"].as<std::string>();
            att.name = row["name"].as<std::string>();
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

void product_category::create(const HttpRequestPtr &req,
                              std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();
    entity::product_category att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
    }
    auto db = database::getDBClient();
    db->execSqlAsync(
        "INSERT INTO anya.product_category(name) VALUES($1) RETURNING sid",
        [&resp](const drogon::orm::Result &result)
        {
            std::string sid;
            for (auto row : result)
            {
                sid = row["sid"].as<std::string>();
            }
            std::string msg_suc = "inserted Succesfully \n product_category ID: " + sid;
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
        att.name);
    callback(resp);
}

void product_category::getOne(const HttpRequestPtr &req,
                              std::function<void(const HttpResponsePtr &)> &&callback,
                              std::string &&sid)
{
    auto resp = HttpResponse::newHttpResponse();
    LOG_DEBUG << "product_category id given " << sid;
    auto db = database::getDBClient();
    db->execSqlAsync(
        "SELECT * FROM anya.product_category WHERE sid=$1 ",
        [&resp, sid](const drogon::orm::Result &result)
        {
            entity::product_category att{};
            att.sid = sid;
            for (auto row : result)
            {
                att.pid = row["pid"].as<int>();
                att.name = row["name"].as<std::string>();
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

void product_category::updateOne(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      std::string &&sid)
{
    auto resp = HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();
    entity::product_category att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
    }
    auto db = database::getDBClient();
    db->execSqlAsync(
        "UPDATE anya.product_category SET name=$1 WHERE sid=$3",
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
        att.name, sid);
        callback(resp);
}

void product_category::deleteOne(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      std::string &&sid)
{
    auto resp = HttpResponse::newHttpResponse();
    auto db = database::getDBClient();
    db->execSqlAsync(
        "DELETE FROM anya.product_category where sid=$1",
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
