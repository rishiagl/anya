#include "rest_api_user.h"
#include <string>

using namespace rest::api;

void user::getUserNames(const HttpRequestPtr req)
{
    auto db = database::getDBClient();
    try
    {
        auto result = co_await db->execSqlCoro("SELECT usrname FROM anya.user");

        std::vector<entity::User> arr;
        for (auto row : result)
        {
            arr.usrname = row["usrname"].as<std::string>();
        }
        std::string buffer = glz::write_json(arr);

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->addHeader("message", std::to_string(arr.size()));
        resp->setContentTypeCode(CT_APPLICATION_JSON);
        resp->setBody(buffer);
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        resp->addHeader("message", e.base().what());
        co_return resp;
    }
}

drogon::Task<drogon::HttpResponsePtr> user::signup(const HttpRequestPtr req)
{
    auto json = req->getJsonObject();
    entity::User att{};
    try
    {
        if (json)
        {
            att.name = (*json)["name"].asInt();
            att.email = (*json)["email"].asString();
            att.usrname = (*json)["usrname"].asString();
            att.passwd = (*json)["passwd"].asString();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "JSON Deserialization error" << e.what() << '\n';

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k422UnprocessableEntity);
        resp->addHeader("message", "User Name not Provided tag = username");
        co_return resp;
    }

    auto db = database::getDBClient();
    try
    {
        auto result = co_await db->execSqlCoro("SELECT usrname FROM anya.user WHERE usrname IN ($1)", att.usrname);
        if (result.size() == 1)
        {
            std::cerr << "JSON Deserialization error" << e.what() << '\n';
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k422UnprocessableEntity);
            resp->addHeader("message", "User Name already present");
            co_return resp;
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        auto result = co_await db->execSqlCoro("INSERT INTO anya.user(name, email, usrname, passwd) VALUES($1, $2, $3, $4) RETURNING pid", att.name, att.email, att.usrname, att.passwd);

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        resp->addHeader("message", "User Added");
        co_return resp;
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        resp->addHeader("message", e.base().what());
        co_return resp;
    }
}

drogon::Task<drogon::HttpResponsePtr> user::signin(const HttpRequestPtr req)
{
    auto json = req->getJsonObject();
    entity::User att{};
    try
    {
        if (json)
        {
            att.usrname = (*json)["usrname"].asString();
            att.passwd = (*json)["passwd"].asString();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "JSON Deserialization error" << e.what() << '\n';

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k422UnprocessableEntity);
        resp->addHeader("message", "User Name not Provided tag = username");

        co_return resp;
    }

    auto db = database::getDBClient();
    try
    {
        auto result = co_await db->execSqlCoro("SELECT usrname, passwd FROM anya.user WHERE usrname IN ($1) RETURNING passwd ", att.usrname);
        if (result.size() == 0)
        {
            std::cerr << "User nOt found" << e.what() << '\n';

            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k404NotFound);
            resp->addHeader("message", "User Does not exists");

            co_return resp;
        }
        else
        {
            std::string db_passwd;
            for (auto row : result)
            {
                db_passwd = row["passwd"].as<std::string>();
            }
            if (db_passwd != att.passwd)
            {
                std::cerr << "Passwd is wrong" << e.what() << '\n';

                auto resp = HttpResponse::newHttpResponse();
                resp->setStatusCode(k401Unauthorized);
                resp->addHeader("message", "Wrong Password");

                co_return resp;
            }
            else
            {
                auto resp = HttpResponse::newHttpResponse();
                resp->setStatusCode(k200OK);
                resp->addHeader("message", "User Signed in");
                co_return resp;
            }
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k500InternalServerError);
        resp->addHeader("message", e.base().what());
        co_return resp;
    }
}
