#include "rest_api_brand.hpp"
#include "../database/database.hpp"
#include <string>
#include <vector>

using namespace rest::api;

void brand::get(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto db = database::getDBClient();
    auto resp = HttpResponse::newHttpResponse();
    db->execSqlAsync(
        "SELECT * FROM anya.brand", [&resp](const drogon::orm::Result &result)
        {
            std::vector<entity::brand> att_arr;
            for (auto row : result)
            {
                entity::brand att{};
                att.pid = row["pid"].as<int>();
                att.sid = row["sid"].as<std::string>();
                att.name = row["name"].as<std::string>();
                att.company_sid = row["company_sid"].as<std::string>();
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

void brand::create(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();
    entity::brand att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
        att.company_sid = (*json)["company_sid"].asString();
    }
    auto db = database::getDBClient();
    db->execSqlAsync(
        "INSERT INTO anya.brand(name, company_sid) VALUES($1, $2) RETURNING sid",
        [&resp](const drogon::orm::Result &result)
        {
            std::string sid;
            for (auto row : result)
            {
                sid = row["sid"].as<std::string>();
            }
            std::string msg_suc = "inserted Succesfully \n Brand ID: " + sid;
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
        att.name, att.company_sid);
    callback(resp);
}

void brand::getOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   std::string &&sid)
{
    auto resp = HttpResponse::newHttpResponse();
    LOG_DEBUG << "brand id given " << sid;
    auto db = database::getDBClient();
    db->execSqlAsync(
        "SELECT * FROM anya.brand WHERE sid=$1 ",
        [&resp, sid](const drogon::orm::Result &result)
        {
            entity::brand att{};
            att.sid = sid;
            for (auto row : result)
            {
                att.pid = row["pid"].as<int>();
                att.name = row["name"].as<std::string>();
                att.company_sid = row["company_sid"].as<std::string>();
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

void brand::updateOne(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      std::string &&sid)
{
    auto resp = HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();
    entity::brand att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
        att.company_sid = (*json)["company_sid"].asString();
    }
    auto db = database::getDBClient();
    db->execSqlAsync(
        "UPDATE anya.brand SET name=$1, company_sid=$2 WHERE sid=$3",
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
        att.name, att.company_sid, sid);
    callback(resp);
}

void brand::deleteOne(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      std::string &&sid)
{
    auto resp = HttpResponse::newHttpResponse();
    auto db = database::getDBClient();
    db->execSqlAsync(
        "DELETE FROM anya.brand where sid=$1",
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
