#include "rest_api_brand.hpp"
#include "../models/brand.hpp"
#include <string>
#include <vector>

using namespace rest::api;

void brand::get(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto att_arr = models::brand::get();
    std::string buffer = glz::write_json(att_arr);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
}

void brand::create(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    models::brand::attributes att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
        att.company_sid = (*json)["company_sid"].asString();
    }
    std::string sid = models::brand::add(att);
    std::string msg_suc = "inserted Succesfully \n Brand ID: " + sid;
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}

void brand::getOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   std::string &&sid)
{
    LOG_DEBUG << "brand id given " << sid;
    auto att = models::brand::get(sid);
    std::string buffer = glz::write_json(att);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
}

void brand::updateOne(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      std::string &&sid)
{
    auto json = req->getJsonObject();
    models::brand::attributes att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
        att.company_sid = (*json)["company_sid"].asString();
    }
    models::brand::update(att, sid);
    std::string msg_suc = "Updated Succesfully";
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}

void brand::deleteOne(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      std::string &&sid)
{
    models::brand::remove(sid);
    std::string msg_suc = "Deleted Succesfully";
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}
