#include "rest_api_company.hpp"
#include "../models/company.hpp"
#include <string>
#include <vector>

using namespace rest::api;

void company::get(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto att_arr = models::company::get();
    std::string buffer = glz::write_json(att_arr);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
}

void company::create(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    models::company::attributes att{};
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
    std::string sid = models::company::add(att);
    std::string msg_suc = "inserted Succesfully \n Company ID: " + sid;
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}

void company::getOne(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string &&sid)
{
    LOG_DEBUG << "Company id given " << sid;
    auto att = models::company::get(sid);
    std::string buffer = glz::write_json(att);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
}

void company::updateOne(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback,
                        std::string &&sid)
{
    auto json = req->getJsonObject();
    models::company::attributes att{};
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
    models::company::update(att, sid);
    std::string msg_suc = "Updated Succesfully";
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}

void company::deleteOne(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback,
                        std::string &&sid)
{
    models::company::remove(sid);
    std::string msg_suc = "Deleted Succesfully";
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
}
