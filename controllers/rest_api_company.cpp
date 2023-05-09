#include "rest_api_company.hpp"
#include "../models/company.hpp"

using namespace rest::api;

// Add definition of your processing function here

void company::get(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback)
{
    // LOG_DEBUG << "Company id given " << id;
    auto c_att_arr = models::company::get();
    std::string buffer = glz::write_json(c_att_arr);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
};

void company::add(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    models::company::attributes c_att{};
    if (json)
    {
        c_att.name = (*json)["name"].asString();
        c_att.address = (*json)["address"].asString();
        c_att.city = (*json)["city"].asString();
        c_att.state = (*json)["state"].asString();
        c_att.country = (*json)["country"].asString();
    }
    std::string cid = models::company::add(c_att);
    std::string msg_suc = "inserted Succesfully \n Company ID: " + cid;
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_PLAIN);
    resp->setBody(msg_suc);
    callback(resp);
};

void company::getById(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback, std::string cid)
{
    LOG_DEBUG << "Company id given " << cid;
    auto c_att = models::company::get(cid);
    std::string buffer = glz::write_json(c_att);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
};