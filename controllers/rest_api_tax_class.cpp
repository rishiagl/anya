#include <string>
#include <vector>
#include "rest_api_tax_class.hpp"
#include "../database/database.hpp"

using namespace rest::api;

drogon::Task<HttpResponsePtr> tax_class::get(const HttpRequestPtr req)
{
    auto db = database::getDBClient();
    try
    {
        // queries the database for companies using coroutine and stores it in result
        auto result = co_await db->execSqlCoro("SELECT * FROM anya.tax_class");

        std::vector<entity::tax_class> att_arr;
        entity::tax_class att{};

        // iterate row over result and push attributes tuples to attribute array;
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.code = row["code"].as<int>();
            att.type_of_code = row["type_of_code"].as<std::string>();
            att.description = row["description"].as<std::string>();
            att.rate = row["rate"].as<int>();
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

drogon::Task<drogon::HttpResponsePtr> tax_class::create(const HttpRequestPtr req)
{
    // get attribute json from request
    auto json = req->getJsonObject();

    // unmarshal json to attribute structure
    entity::tax_class att{};
    if (json)
    {
        att.code = (*json)["code"].asInt();
        att.type_of_code = (*json)["type_of_code"].asString();
        att.description = (*json)["description"].asString();
        att.rate = (*json)["rate"].asInt();
    }

    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("INSERT INTO anya.tax_class(code, type_of_code, description, rate) VALUES($1, $2, $3, $4) RETURNING code", att.code, att.type_of_code, att.description, att.rate);

        // get code of inserted row
        int code;
        for (auto row : result)
        {
            code = row["code"].as<int>();
        }
        std::string msg_suc = "inserted Succesfully \n tax_class ID: " + code;

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

drogon::Task<drogon::HttpResponsePtr> tax_class::getOne(const HttpRequestPtr req, int code)
{
    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("SELECT * FROM anya.tax_class WHERE code=$1", code);

        entity::tax_class att{};
        att.code = code;

        // iterate over result and get attributes
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.type_of_code = row["type_of_code"].as<std::string>();
            att.description = row["description"].as<std::string>();
            att.rate = row["row"].as<int>();
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

drogon::Task<drogon::HttpResponsePtr> tax_class::updateOne(const HttpRequestPtr req, int code)
{
    // get attributes for update from request
    auto json = req->getJsonObject();

    // unmarshall json
    entity::tax_class att{};
    if (json)
    {
        att.code = (*json)["code"].asInt();
        att.type_of_code = (*json)["type_of_code"].asString();
        att.description = (*json)["description"].asString();
        att.rate = (*json)["rate"].asInt();
    }

    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("UPDATE anya.tax_class SET type_of_code=$1, description=$2, rate=$3 WHERE code=$4", att.type_of_code, att.description, att.rate, code);

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

drogon::Task<drogon::HttpResponsePtr> tax_class::deleteOne(const HttpRequestPtr req, int code)
{
    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("DELETE FROM anya.tax_class where code=$1", code);

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
