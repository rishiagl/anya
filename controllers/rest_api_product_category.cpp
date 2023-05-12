#include "rest_api_product_category.hpp"
#include "../models/product_category.hpp"
#include <string>
#include <vector>

using namespace rest::api;

void product_category::get(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto att_arr = models::product_category::get();
    std::string buffer = glz::write_json(att_arr);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
}

void product_category::create(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    models::product_category::attributes att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
    }
    std::string sid = models::product_category::add(att);
    std::string msg_suc = "inserted Succesfully \n product_category ID: " + sid;
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}

void product_category::getOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   std::string &&sid)
{
    LOG_DEBUG << "product_category id given " << sid;
    auto att = models::product_category::get(sid);
    std::string buffer = glz::write_json(att);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
}

void product_category::updateOne(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      std::string &&sid)
{
    auto json = req->getJsonObject();
    models::product_category::attributes att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
    }
    models::product_category::update(att, sid);
    std::string msg_suc = "Updated Succesfully";
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}

void product_category::deleteOne(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      std::string &&sid)
{
    models::product_category::remove(sid);
    std::string msg_suc = "Deleted Succesfully";
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}
