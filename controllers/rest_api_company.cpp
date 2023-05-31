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

        auto resp = HttpResponse::newHttpResponse();

        // status code set to success
        resp->setStatusCode(k200OK);

        // Add message
        resp->addHeader("message", std::to_string(att_arr.size()));

        // content type JSON
        resp->setContentTypeCode(CT_APPLICATION_JSON);
        resp->setBody(buffer);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";

        // print error
        std::cerr << "error:" << e.base().what() << std::endl;

        auto resp = HttpResponse::newHttpResponse();

        // set status code to internal server error
        resp->setStatusCode(k500InternalServerError);

        // set a error to message in http header
        resp->addHeader("message", e.base().what());

        co_return resp;
    }
}

drogon::Task<drogon::HttpResponsePtr> company::create(const HttpRequestPtr req)
{
    // get attribute json from request
    auto json = req->getJsonObject();

    // unmarshal json to attribute structure
    entity::company att{};
    try
    {
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
    }
    catch (const std::exception &e)
    {
        std::cerr << "JSON Deserialization error" << e.what() << '\n';

        auto resp = HttpResponse::newHttpResponse();

        // set status code to internal server error
        resp->setStatusCode(k422UnprocessableEntity);

        // set a error to message in http header
        resp->addHeader("message", e.what());

        co_return resp;
    }

    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("INSERT INTO anya.company(name, address, city, state, country, cin, pan, gstin) VALUES($1, $2, $3, $4, $5, $6, $7, $8) RETURNING pid", att.name, att.address, att.city, att.state, att.country, att.cin, att.pan, att.gstin);

        // get sid of inserted row
        int pid;
        for (auto row : result)
        {
            pid = row["pid"].as<int>();
        }
        std::string msg_suc = "inserted Succesfully \n Company ID: " + std::to_string(pid);

        // send response
        auto resp = HttpResponse::newHttpResponse();

        // set http code to 200
        resp->setStatusCode(k200OK);

        // add message
        resp->addHeader("message", msg_suc);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        std::cerr << "error:" << e.base().what() << std::endl;

        // send response
        auto resp = HttpResponse::newHttpResponse();

        // set status code to 422
        resp->setStatusCode(k422UnprocessableEntity);

        // add error message to header
        resp->addHeader("message", e.base().what());
        co_return resp;
    }
}

drogon::Task<drogon::HttpResponsePtr> company::getOne(const HttpRequestPtr req, int pid)
{
    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("SELECT * FROM anya.company WHERE pid=$1", pid);

        entity::company att{};

        if (result.size() == 0)
        {
            // send response
            auto resp = HttpResponse::newHttpResponse();

            // set status code to 422
            resp->setStatusCode(k404NotFound);

            // add error message to header
            std::string str = std::to_string(pid) + " not present in database";
            resp->addHeader("message", str);

            co_return resp;
        }

        att.pid = pid;

        // iterate over result and get attributes
        for (auto row : result)
        {
            att.sid = row["sid"].as<std::string>();
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

        auto resp = HttpResponse::newHttpResponse();

        // status code set to success
        resp->setStatusCode(k200OK);

        // Add message
        resp->addHeader("message", "Success");

        // content type JSON
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

        // set status code to 500
        resp->setStatusCode(k500InternalServerError);

        // add error message to header
        resp->addHeader("message", e.base().what());
        co_return resp;
    }
}

drogon::Task<drogon::HttpResponsePtr> company::updateOne(const HttpRequestPtr req, int pid)
{
    // get attributes for update from request
    auto json = req->getJsonObject();

    // unmarshall json
    entity::company att{};

    try
    {
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
    }
    catch (const std::exception &e)
    {
        std::cerr << "JSON Deserialization error" << e.what() << '\n';

        auto resp = HttpResponse::newHttpResponse();

        // set status code to internal server error
        resp->setStatusCode(k422UnprocessableEntity);

        // set a error to message in http header
        resp->addHeader("message", e.what());

        co_return resp;
    }

    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("UPDATE anya.company SET name=$1, address=$2, city=$3, state=$4, country=$5, cin=$6, pan=$7, gstin=$8 WHERE pid=$9", att.name, att.address, att.city, att.state, att.country, att.cin, att.pan, att.gstin, pid);

        // send positive response
        auto resp = HttpResponse::newHttpResponse();

        resp->setStatusCode(k200OK);

        // add message
        std::string msg_suc = "Updated Succesfully";
        resp->addHeader("message", msg_suc);

        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;

        auto resp = HttpResponse::newHttpResponse();

        // set status code to internal server error
        resp->setStatusCode(k422UnprocessableEntity);

        // set a error to message in http header
        resp->addHeader("message", e.base().what());

        co_return resp;
    }
}

drogon::Task<drogon::HttpResponsePtr> company::deleteOne(const HttpRequestPtr req, int pid)
{
    auto db = database::getDBClient();

    try
    {
        auto result = co_await db->execSqlCoro("DELETE FROM anya.company where pid=$1", pid);

        // print affected rows count
        LOG_DEBUG << result.affectedRows();

        if (result.affectedRows() == 0)
        {
            auto resp = HttpResponse::newHttpResponse();

            // set status code to 422
            resp->setStatusCode(k404NotFound);

            // add error message to header
            std::string str = std::to_string(pid) + "Not present in database";
            resp->addHeader("message", str);

            co_return resp;
        }

        auto resp = HttpResponse::newHttpResponse();

        resp->setStatusCode(k200OK);

        // add message
        std::string msg_suc = "Deleted Succesfully";
        resp->addHeader("message", msg_suc);

        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        std::cerr << "error:" << e.base().what() << std::endl;

        // send response
        auto resp = HttpResponse::newHttpResponse();

        // set status code to 500
        resp->setStatusCode(k500InternalServerError);

        // add error message to header
        resp->addHeader("message", e.base().what());
        co_return resp;
    }
}
