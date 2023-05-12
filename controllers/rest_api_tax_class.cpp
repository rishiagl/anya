#include "rest_api_tax_class.hpp"
#include "../models/tax_class.hpp"
#include <string>
#include <vector>

using namespace rest::api;

void tax_class::get(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto att_arr = models::tax_class::get();
    std::string buffer = glz::write_json(att_arr);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
}

void tax_class::create(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    models::tax_class::attributes att{};
    if (json)
    {
        att.code = (*json)["code"].asInt();
        att.type_of_code = (*json)["type_of_code"].asString();
        att.description = (*json)["description"].asString();
        att.rate = (*json)["rate"].asInt();
    }
    int code = models::tax_class::add(att);
    std::string msg_suc = "inserted Succesfully \n tax_class ID: " + code;
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}

void tax_class::getOne(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback,
                       int &&code)
{
    LOG_DEBUG << "tax_class id given " << code;
    auto att = models::tax_class::get(code);
    std::string buffer = glz::write_json(att);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
}

void tax_class::updateOne(const HttpRequestPtr &req,
                          std::function<void(const HttpResponsePtr &)> &&callback,
                          int &&code)
{
    auto json = req->getJsonObject();
    models::tax_class::attributes att{};
    if (json)
    {
        att.code = (*json)["code"].asInt();
        att.type_of_code = (*json)["type_of_code"].asString();
        att.description = (*json)["description"].asString();
        att.rate = (*json)["rate"].asInt();
    }
    models::tax_class::update(att, code);
    std::string msg_suc = "Updated Succesfully";
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}

void tax_class::deleteOne(const HttpRequestPtr &req,
                          std::function<void(const HttpResponsePtr &)> &&callback,
                          int &&code)
{
    models::tax_class::remove(code);
    std::string msg_suc = "Deleted Succesfully";
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}
