#pragma once

#include <drogon/HttpController.h>
#include <drogon/utils/coroutine.h>
#include <coroutine>

using namespace drogon;

namespace rest
{
  namespace api
  {
    class tax_class : public drogon::HttpController<tax_class>
    {
    public:
      METHOD_LIST_BEGIN

      METHOD_ADD(tax_class::get, "", Get);
      METHOD_ADD(tax_class::create, "", Post, Options);
      METHOD_ADD(tax_class::getOne, "/{code}", Get, Options);
      METHOD_ADD(tax_class::updateOne, "/{code}", Put, Options);
      METHOD_ADD(tax_class::deleteOne, "/{code}", Delete, Options);

      METHOD_LIST_END

      drogon::Task<HttpResponsePtr> getOne(const HttpRequestPtr req, int code);
      drogon::Task<HttpResponsePtr> updateOne(const HttpRequestPtr req, int code);
      drogon::Task<HttpResponsePtr> deleteOne(const HttpRequestPtr req, int code);
      drogon::Task<HttpResponsePtr> get(const HttpRequestPtr req);
      drogon::Task<HttpResponsePtr> create(const HttpRequestPtr req);
    };
  }
}
