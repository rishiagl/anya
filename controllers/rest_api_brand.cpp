#include <string>
#include <vector>
#include "rest_api_brand.hpp"
#include "../database/database.hpp"

using namespace rest::api;

drogon::Task<HttpResponsePtr> brand::get(const HttpRequestPtr req)
{
    auto db = database::getDBClient();
    try
    {
        // queries the database for companies using coroutine and stores it in result
        auto result = co_await db->execSqlCoro("SELECT * FROM anya.brand");

        std::vector<entity::brand> att_arr;
        entity::brand att{};

        // iterate row over result and push attributes tuples to attribute array;
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.sid = row["sid"].as<std::string>();
            att.name = row["name"].as<std::string>();
            att.company_sid = row["company_sid"].as<std::string>();
            att_arr.push_back(att);
        }

        // buffer stores attribute array in json format
        std::string buffer = glz::write_json(att_arr);

        // populate response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setContentTypeCode(CT_APPLICATION_JSON);
        resp->setBody(buffer);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";

        // print error
        std::cerr << "error:" << e.base().what() << std::endl;

        // populate response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        resp->setContentTypeCode(CT_TEXT_PLAIN);
        resp->setBody(e.base().what());
        co_return resp;
    }
}

drogon::Task<drogon::HttpResponsePtr> brand::create(const HttpRequestPtr req)
{
    // get attribute json from request
    auto json = req->getJsonObject();

    // unmarshal json to attribute structure
    entity::brand att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
        att.company_sid = (*json)["company_sid"].asString();
    }

    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("INSERT INTO anya.brand(name, company_sid) VALUES($1, $2) RETURNING sid", att.name, att.company_sid);

        // get sid of inserted row
        std::string sid;
        for (auto row : result)
        {
            sid = row["sid"].as<std::string>();
        }
        std::string msg_suc = "inserted Succesfully \n brand ID: " + sid;

        // send response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setContentTypeCode(CT_TEXT_PLAIN);
        resp->setBody(msg_suc);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;

        // send response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k422UnprocessableEntity);
        resp->setContentTypeCode(CT_TEXT_PLAIN);
        resp->setBody(e.base().what());
        co_return resp;
    }
}

drogon::Task<drogon::HttpResponsePtr> brand::getOne(const HttpRequestPtr req, std::string sid)
{
    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("SELECT * FROM anya.brand WHERE sid=$1", sid);

        entity::brand att{};
        att.sid = sid;

        // iterate over result and get attributes
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.name = row["name"].as<std::string>();
            att.company_sid = row["company_sid"].as<std::string>();
        }

        // store attributes as json in buffer string
        std::string buffer = glz::write_json(att);

        // send response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setContentTypeCode(CT_APPLICATION_JSON);
        resp->setBody(buffer);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;

        // send response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        resp->setContentTypeCode(CT_TEXT_PLAIN);
        resp->setBody(e.base().what());
        co_return resp;
    }
}

drogon::Task<drogon::HttpResponsePtr> brand::updateOne(const HttpRequestPtr req, std::string sid)
{
    // get attributes for update from request
    auto json = req->getJsonObject();

    // unmarshall json
    entity::brand att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
        att.company_sid = (*json)["company_sid"].asString();
    }

    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("UPDATE anya.brand SET name=$1, company_sid=$2 WHERE sid=$3", att.name, att.company_sid, sid);

        // send positive response
        auto resp = HttpResponse::newHttpResponse();
        std::string msg_suc = "Updated Succesfully";
        resp->setStatusCode(k200OK);
        resp->setContentTypeCode(CT_TEXT_PLAIN);
        resp->setBody(msg_suc);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;

        // send negative response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k422UnprocessableEntity);
        resp->setContentTypeCode(CT_TEXT_PLAIN);
        resp->setBody(e.base().what());
        co_return resp;
    }
}

drogon::Task<drogon::HttpResponsePtr> brand::deleteOne(const HttpRequestPtr req, std::string sid)
{
    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("DELETE FROM anya.brand where sid=$1", sid);

        // print affected rows count
        LOG_DEBUG << result.affectedRows();
        std::string msg_suc = "Deleted Succesfully";

        // send positive response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->setContentTypeCode(CT_TEXT_PLAIN);
        resp->setBody(msg_suc);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        std::cerr << "error:" << e.base().what() << std::endl;

        // negatve response
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        resp->setContentTypeCode(CT_TEXT_PLAIN);
        resp->setBody(e.base().what());
        co_return resp;
    }
}