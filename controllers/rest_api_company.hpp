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
      METHOD_ADD(company::getOne, "/{pid}", Get, Options);
      METHOD_ADD(company::updateOne, "/{pid}", Put, Options);
      METHOD_ADD(company::deleteOne, "/{pid}", Delete, Options);

      METHOD_LIST_END

      drogon::Task<HttpResponsePtr> getOne(const HttpRequestPtr req, int pid);
      drogon::Task<HttpResponsePtr> updateOne(const HttpRequestPtr req, int pid);
      drogon::Task<HttpResponsePtr> deleteOne(const HttpRequestPtr req, int pid);
      drogon::Task<HttpResponsePtr> get(const HttpRequestPtr req);
      drogon::Task<HttpResponsePtr> create(const HttpRequestPtr req);
    };
  }
}
