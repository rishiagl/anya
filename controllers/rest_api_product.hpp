#pragma once

#include <drogon/HttpController.h>
#include <drogon/utils/coroutine.h>
#include <coroutine>

using namespace drogon;

namespace rest
{
  namespace api
  {
    class product : public drogon::HttpController<product>
    {
    public:
      METHOD_LIST_BEGIN

      METHOD_ADD(product::get, "", Get);
      METHOD_ADD(product::create, "", Post, Options);
      METHOD_ADD(product::getOne, "/{sid}", Get, Options);
      METHOD_ADD(product::updateOne, "/{sid}", Put, Options);
      METHOD_ADD(product::deleteOne, "/{sid}", Delete, Options);

      METHOD_LIST_END

      drogon::Task<HttpResponsePtr> getOne(const HttpRequestPtr req, std::string sid);
      drogon::Task<HttpResponsePtr> updateOne(const HttpRequestPtr req, std::string sid);
      drogon::Task<HttpResponsePtr> deleteOne(const HttpRequestPtr req, std::string sid);
      drogon::Task<HttpResponsePtr> get(const HttpRequestPtr req);
      drogon::Task<HttpResponsePtr> create(const HttpRequestPtr req);
    };
  }
}