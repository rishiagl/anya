#pragma once

#include <drogon/HttpController.h>
#include <drogon/utils/coroutine.h>
#include <coroutine>

using namespace drogon;

namespace rest
{
  namespace api
  {
    class company : public drogon::HttpController<company>
    {
    public:
      METHOD_LIST_BEGIN

      METHOD_ADD(company::get, "", Get);
      METHOD_ADD(company::create, "", Post, Options);
      METHOD_ADD(company::getOne, "/{sid}", Get, Options);
      METHOD_ADD(company::updateOne, "/{sid}", Put, Options);
      METHOD_ADD(company::deleteOne, "/{sid}", Delete, Options);

      METHOD_LIST_END

      drogon::Task<HttpResponsePtr> getOne(const HttpRequestPtr req, std::string sid);
      drogon::Task<HttpResponsePtr> updateOne(const HttpRequestPtr req, std::string sid);
      drogon::Task<HttpResponsePtr> deleteOne(const HttpRequestPtr req, std::string sid);
      drogon::Task<HttpResponsePtr> get(const HttpRequestPtr req);
      drogon::Task<HttpResponsePtr> create(const HttpRequestPtr req);
    };
  }
}
