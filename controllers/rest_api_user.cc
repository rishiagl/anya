#include "rest_api_user.h"
#include <string>
#include "utils/response.hpp"

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

        co_return response::newResponse(k200OK, std::to_string(arr.size()), CT_APPLICATION_JSON, buffer);
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
        co_return response::newResponse(k500InternalServerError, e.base().what());
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

        co_return response::newResponse(k422UnprocessableEntity, "User Name not Provided tag = username");
    }

    auto db = database::getDBClient();
    try
    {
        auto result = co_await db->execSqlCoro("SELECT usrname FROM anya.user WHERE usrname IN ($1)", att.usrname);
        if (result.size() == 1)
        {
            std::cerr << "JSON Deserialization error" << e.what() << '\n';
            co_return response::newResponse(k422UnprocessableEntity, "User Name already present");
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        auto result = co_await db->execSqlCoro("INSERT INTO anya.user(name, email, usrname, passwd) VALUES($1, $2, $3, $4) RETURNING pid", att.name, att.email, att.usrname, att.passwd);
        co_return response::newResponse(k200OK, "User Added");
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
        co_return response::newResponse(k500InternalServerError, e.base().what());
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
        co_return co_return response::newResponse(k422UnprocessableEntity, "User Name not Provided tag = username");
    }

    auto db = database::getDBClient();
    try
    {
        auto result = co_await db->execSqlCoro("SELECT usrname, passwd FROM anya.user WHERE usrname IN ($1) RETURNING passwd ", att.usrname);
        if (result.size() == 0)
        {
            std::cerr << "User nOt found" << e.what() << '\n';
            co_return response::newResponse(k404NotFound, "User Does not exists");
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
                co_return response::newResponse(k401Unauthorized, "Wrong Password");
            }
            else
            {
                co_return response::newResponse(k200OK, "User Signed in");
            }
        }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        LOG_DEBUG << "ERROR CATCHED";
        std::cerr << "error:" << e.base().what() << std::endl;
        co_return response::newResponse(k500InternalServerError, e.base().what());
    }
}
