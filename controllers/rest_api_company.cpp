#include <string>
#include <vector>
#include "rest_api_company.hpp"
#include "../database/database.hpp"

using namespace rest::api;

void company::get(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newHttpResponse();
    auto db = database::getDBClient();
    db->execSqlAsync(
        "SELECT * FROM anya.company",
        [&resp](const drogon::orm::Result &result)
        {
            std::vector<entity::company> att_arr;
            entity::company att{};
            for (auto row : result)
            {
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
            std::string buffer = glz::write_json(att_arr);
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
        });
    callback(resp);
}

void company::create(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();
    entity::company att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
        att.address = (*json)["address"].asString();
        att.city = (*json)["city"].asString();
        att.state = (*json)["state"].asString();
        att.country = (*json)["country"].asString();
        att.cin = (*json)["cin"].asString();
        att.pan = (*json)["pan"].asString();
        att.gstin = (*json)["gstin"].asString();
    }
    auto db = database::getDBClient();
    db->execSqlAsync(
        "INSERT INTO anya.company(name, address, city, state, country, cin, pan, gstin) VALUES($1, $2, $3, $4, $5, $6, $7, $8) RETURNING sid",
        [&resp](const drogon::orm::Result &result)
        {
            std::string sid;
            for (auto row : result)
            {
                sid = row["sid"].as<std::string>();
            }
            std::string msg_suc = "inserted Succesfully \n Company ID: " + sid;
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
        att.name, att.address, att.city, att.state, att.country, att.cin, att.pan, att.gstin);
    callback(resp);
}

void company::getOne(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string &&sid)
{
    auto resp = HttpResponse::newHttpResponse();
    LOG_DEBUG << "Company id given " << sid;
    auto db = database::getDBClient();
    db->execSqlAsync(
        "SELECT * FROM anya.company WHERE sid=$1",
        [&resp, sid](const drogon::orm::Result &result)
        {
            entity::company att{};
            att.sid = sid;
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

void company::updateOne(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback,
                        std::string &&sid)
{
    auto resp = HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();
    entity::company att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
        att.address = (*json)["address"].asString();
        att.city = (*json)["city"].asString();
        att.state = (*json)["state"].asString();
        att.country = (*json)["country"].asString();
        att.cin = (*json)["cin"].asString();
        att.pan = (*json)["pan"].asString();
        att.gstin = (*json)["gstin"].asString();
    }
    auto db = database::getDBClient();
    db->execSqlAsync(
        "UPDATE anya.company SET name=$1, address=$2, city=$3, state=$4, country=$5, cin=$6, pan=$7, gstin=$8 WHERE sid=$9",
        [&resp](const drogon::orm::Result &e)
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
        att.name, att.address, att.city, att.state, att.country, att.cin, att.pan, att.gstin, sid);
    callback(resp);
}

void company::deleteOne(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback,
                        std::string &&sid)
{
    auto resp = HttpResponse::newHttpResponse();
    auto db = database::getDBClient();
    db->execSqlAsync(
        "DELETE FROM anya.company where sid=$1",
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
