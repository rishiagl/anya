#include "rest_api_company.hpp"
#include "../models/company.hpp"

using namespace rest::api;

// Add definition of your processing function here

void company::get(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback, int id)
{
    LOG_DEBUG << "Company id given " << id;
    auto c_att = models::company::get(id);
    std::string buffer = glz::write_json(c_att);
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(buffer);
    callback(resp);
};