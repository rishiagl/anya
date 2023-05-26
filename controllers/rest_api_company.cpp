#include <string>
#include <vector>
#include "rest_api_company.hpp"
#include "../database/database.hpp"

using namespace rest::api;

drogon::Task<HttpResponsePtr> company::get(const HttpRequestPtr req)
{
    auto db = database::getDBClient();
    try
    {
        // queries the database for companies using coroutine and stores it in result
        auto result = co_await db->execSqlCoro("SELECT * FROM anya.company");

        std::vector<entity::company> att_arr;
        entity::company att{};

        // iterate row over result and push attributes tuples to attribute array;
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

drogon::Task<drogon::HttpResponsePtr> company::create(const HttpRequestPtr req)
{
    // get attribute json from request
    auto json = req->getJsonObject();

    // unmarshal json to attribute structure
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

    try
    {
        auto result = co_await db->execSqlCoro("INSERT INTO anya.company(name, address, city, state, country, cin, pan, gstin) VALUES($1, $2, $3, $4, $5, $6, $7, $8) RETURNING sid", att.name, att.address, att.city, att.state, att.country, att.cin, att.pan, att.gstin);

        // get sid of inserted row
        std::string sid;
        for (auto row : result)
        {
            sid = row["sid"].as<std::string>();
        }
        std::string msg_suc = "inserted Succesfully \n Company ID: " + sid;

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

drogon::Task<drogon::HttpResponsePtr> company::getOne(const HttpRequestPtr req, std::string sid)
{
    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("SELECT * FROM anya.company WHERE sid=$1", sid);

        entity::company att{};
        att.sid = sid;

        // iterate over result and get attributes
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

drogon::Task<drogon::HttpResponsePtr> company::updateOne(const HttpRequestPtr req, std::string sid)
{
    // get attributes for update from request
    auto json = req->getJsonObject();

    // unmarshall json
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

    try
    {
        auto result = co_await db->execSqlCoro("UPDATE anya.company SET name=$1, address=$2, city=$3, state=$4, country=$5, cin=$6, pan=$7, gstin=$8 WHERE sid=$9", att.name, att.address, att.city, att.state, att.country, att.cin, att.pan, att.gstin, sid);

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

drogon::Task<drogon::HttpResponsePtr> company::deleteOne(const HttpRequestPtr req, std::string sid)
{
    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("DELETE FROM anya.company where sid=$1", sid);

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
