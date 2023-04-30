#include "rest_api_company.h"

using namespace rest::api;

// Add definition of your processing function here

void company::getById(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback, int id)
{
    LOG_DEBUG<<"Company id given "<<id;
    //Authentication algorithm, read database, verify, identify, etc...
    //...
    Json::Value ret;
    ret["result"]="ok";
    ret["token"]=drogon::utils::getUuid();
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
};