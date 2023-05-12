#include "rest_api_product.hpp"
#include "../models/product.hpp"
#include <string>
#include <vector>

using namespace rest::api;

void product::get(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto att_arr = models::product::get();
    std::string buffer = glz::write_json(att_arr);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
}

void product::create(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    models::product::attributes att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
        att.brand_sid = (*json)["brand_sid"].asString();
        att.category_sid = (*json)["category_sid"].asString();
        att.tax_class_code = (*json)["tax_class_code"].asString();
        att.type_of_supply = (*json)["type_of_supply"].asString();
    }
    std::string sid = models::product::add(att);
    std::string msg_suc = "inserted Succesfully \n product ID: " + sid;
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}

void product::getOne(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string &&sid)
{
    LOG_DEBUG << "product id given " << sid;
    auto att = models::product::get(sid);
    std::string buffer = glz::write_json(att);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
}

void product::updateOne(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback,
                        std::string &&sid)
{
    auto json = req->getJsonObject();
    models::product::attributes att{};
    if (json)
    {
        att.name = (*json)["name"].asString();
        att.brand_sid = (*json)["brand_sid"].asString();
        att.category_sid = (*json)["category_sid"].asString();
        att.tax_class_code = (*json)["tax_class_code"].asString();
        att.type_of_supply = (*json)["type_of_supply"].asString();
    }
    models::product::update(att, sid);
    std::string msg_suc = "Updated Succesfully";
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}

void product::deleteOne(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback,
                        std::string &&sid)
{
    models::product::remove(sid);
    std::string msg_suc = "Deleted Succesfully";
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}