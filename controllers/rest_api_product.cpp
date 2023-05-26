#include <string>
#include <vector>
#include "rest_api_product.hpp"
#include "../database/database.hpp"

using namespace rest::api;

drogon::Task<HttpResponsePtr> product::get(const HttpRequestPtr req)
{
    auto db = database::getDBClient();
    try
    {
        // queries the database for companies using coroutine and stores it in result
        auto result = co_await db->execSqlCoro("SELECT * FROM anya.product");

        std::vector<entity::product> att_arr;
        entity::product att{};

        // iterate row over result and push attributes tuples to attribute array;
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.sid = row["sid"].as<std::string>();
            att.name = row["name"].as<std::string>();
            att.brand_sid = row["brand_sid"].as<std::string>();
            att.category_sid = row["category_sid"].as<std::string>();
            att.tax_class_code = row["tax_class_code"].as<std::string>();
            att.type_of_supply = row["type_of_supply"].as<std::string>();
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

drogon::Task<drogon::HttpResponsePtr> product::create(const HttpRequestPtr req)
{
    // get attribute json from request
    auto json = req->getJsonObject();

    // unmarshal json to attribute structure
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

    try
    {
        auto result = co_await db->execSqlCoro("INSERT INTO anya.product(name, brand_sid, category_sid, tax_class_code, type_of_supply) VALUES($1, $2, $3, $4, $5) RETURNING sid", att.name, att.brand_sid, att.category_sid, att.tax_class_code, att.type_of_supply);

        // get sid of inserted row
        std::string sid;
        for (auto row : result)
        {
            sid = row["sid"].as<std::string>();
        }
        std::string msg_suc = "inserted Succesfully \n product ID: " + sid;

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

drogon::Task<drogon::HttpResponsePtr> product::getOne(const HttpRequestPtr req, std::string sid)
{
    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("SELECT * FROM anya.product WHERE sid=$1", sid);

        entity::product att{};
        att.sid = sid;

        // iterate over result and get attributes
        for (auto row : result)
        {
            att.pid = row["pid"].as<int>();
            att.name = row["name"].as<std::string>();
            att.brand_sid = row["brand_sid"].as<std::string>();
            att.category_sid = row["category_sid"].as<std::string>();
            att.tax_class_code = row["tax_class_code"].as<std::string>();
            att.type_of_supply = row["type_of_supply"].as<std::string>();
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

drogon::Task<drogon::HttpResponsePtr> product::updateOne(const HttpRequestPtr req, std::string sid)
{
    // get attributes for update from request
    auto json = req->getJsonObject();

    // unmarshall json
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

    try
    {
        auto result = co_await db->execSqlCoro("UPDATE anya.product SET name=$1, brand_sid=$2, category_sid=$3, tax_class_code=$4, type_of_supply=$5 WHERE sid=$6", att.name, att.brand_sid, att.category_sid, att.tax_class_code, att.type_of_supply, sid);

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

drogon::Task<drogon::HttpResponsePtr> product::deleteOne(const HttpRequestPtr req, std::string sid)
{
    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("DELETE FROM anya.product where sid=$1", sid);

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
