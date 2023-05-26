#include <string>
#include <vector>
#include "rest_api_product_category.hpp"
#include "../database/database.hpp"

using namespace rest::api;

drogon::Task<HttpResponsePtr> product_category::get(const HttpRequestPtr req)
{
    auto db = database::getDBClient();
    try
    {
        // queries the database for companies using coroutine and stores it in result
        auto result = co_await db->execSqlCoro("SELECT * FROM anya.product_category");

        std::vector<entity::product_category> att_arr;
        entity::product_category att{};

        // iterate row over result and push attributes tuples to attribute array;
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.sid = row["sid"].as<std::string>();
            att.name = row["name"].as<std::string>();
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

drogon::Task<drogon::HttpResponsePtr> product_category::create(const HttpRequestPtr req)
{
    // get attribute json from request
    auto json = req->getJsonObject();

    // unmarshal json to attribute structure
    entity::product_category att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
    }

    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("INSERT INTO anya.product_category(name) VALUES($1) RETURNING sid", att.name);

        // get sid of inserted row
        std::string sid;
        for (auto row : result)
        {
            sid = row["sid"].as<std::string>();
        }
        std::string msg_suc = "inserted Succesfully \n product_category ID: " + sid;

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

drogon::Task<drogon::HttpResponsePtr> product_category::getOne(const HttpRequestPtr req, std::string sid)
{
    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("SELECT * FROM anya.product_category WHERE sid=$1", sid);

        entity::product_category att{};
        att.sid = sid;

        // iterate over result and get attributes
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.name = row["name"].as<std::string>();
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

drogon::Task<drogon::HttpResponsePtr> product_category::updateOne(const HttpRequestPtr req, std::string sid)
{
    // get attributes for update from request
    auto json = req->getJsonObject();

    // unmarshall json
    entity::product_category att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
    }

    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("UPDATE anya.product_category SET name=$1 WHERE sid=$3", att.name, sid);

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

drogon::Task<drogon::HttpResponsePtr> product_category::deleteOne(const HttpRequestPtr req, std::string sid)
{
    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("DELETE FROM anya.product_category where sid=$1", sid);

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