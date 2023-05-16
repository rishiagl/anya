#include "rest_api_tax_class.hpp"
#include "../database/database.hpp"
#include <string>
#include <vector>

using namespace rest::api;

void tax_class::get(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto db = database::getDBClient();
    auto resp = HttpResponse::newHttpResponse();
    db->execSqlAsync(
        "SELECT * FROM anya.tax_class", [&resp](const drogon::orm::Result &result)
        {
        std::vector<entity::tax_class> att_arr;
        for (auto row : result)
        {
            entity::tax_class att{};
            att.pid = row["pid"].as<int>();
            att.code = row["code"].as<int>();
            att.type_of_code = row["type_of_code"].as<std::string>();
            att.description = row["description"].as<std::string>();
            att.rate = row["rate"].as<int>();
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

void tax_class::create(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();
    entity::tax_class att{};
    if (json)
    {
        att.code = (*json)["code"].asInt();
        att.type_of_code = (*json)["type_of_code"].asString();
        att.description = (*json)["description"].asString();
        att.rate = (*json)["rate"].asInt();
    }
    auto db = database::getDBClient();
    db->execSqlAsync(
        "INSERT INTO anya.tax_class(code, type_of_code, description, rate) VALUES($1, $2, $3, $4) RETURNING code",
        [&resp](const drogon::orm::Result &result)
        {
            std::string code;
            for (auto row : result)
            {
                code = row["code"].as<std::string>();
            }
            std::string msg_suc = "inserted Succesfully \n tax_class ID: " + code;
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
        att.code, att.type_of_code, att.description, att.rate);
    callback(resp);
}

void tax_class::getOne(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback,
                       int &&code)
{
    auto resp = HttpResponse::newHttpResponse();
    LOG_DEBUG << "tax_class id given " << code;
    auto db = database::getDBClient();
    db->execSqlAsync(
        "SELECT * FROM anya.tax_class WHERE code=$1 ",
        [&resp, code](const drogon::orm::Result &result)
        {
            entity::tax_class att{};
            att.code = code;
            for (auto row : result)
            {
                att.pid = row["pid"].as<int>();
                att.type_of_code = row["type_of_code"].as<std::string>();
                att.description = row["description"].as<std::string>();
                att.rate = row["row"].as<int>();
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
        code);
    callback(resp);
}

void tax_class::updateOne(const HttpRequestPtr &req,
                          std::function<void(const HttpResponsePtr &)> &&callback,
                          int &&code)
{
    auto resp = HttpResponse::newHttpResponse();
    auto json = req->getJsonObject();
    entity::tax_class att{};
    if (json)
    {
        att.code = (*json)["code"].asInt();
        att.type_of_code = (*json)["type_of_code"].asString();
        att.description = (*json)["description"].asString();
        att.rate = (*json)["rate"].asInt();
    }
    auto db = database::getDBClient();
    db->execSqlAsync(
        "UPDATE anya.tax_class SET type_of_code=$1, description=$2, rate=$3 WHERE code=$4",
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
        att.type_of_code, att.description, att.rate, code);
    callback(resp);
}

void tax_class::deleteOne(const HttpRequestPtr &req,
                          std::function<void(const HttpResponsePtr &)> &&callback,
                          int &&code)
{
    auto resp = HttpResponse::newHttpResponse();
    auto db = database::getDBClient();
    db->execSqlAsync(
        "DELETE FROM anya.tax_class where code=$1",
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
        code);
    callback(resp);
}
