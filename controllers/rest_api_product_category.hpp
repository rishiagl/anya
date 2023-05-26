#pragma once

#include <drogon/HttpController.h>
#include <drogon/utils/coroutine.h>
#include <coroutine>

using namespace drogon;

namespace rest
{
  namespace api
  {
    class product_category : public drogon::HttpController<product_category>
    {
    public:
      METHOD_LIST_BEGIN

      METHOD_ADD(product_category::get, "", Get);
      METHOD_ADD(product_category::create, "", Post, Options);
      METHOD_ADD(product_category::getOne, "/{sid}", Get, Options);
      METHOD_ADD(product_category::updateOne, "/{sid}", Put, Options);
      METHOD_ADD(product_category::deleteOne, "/{sid}", Delete, Options);

      METHOD_LIST_END

      drogon::Task<HttpResponsePtr> getOne(const HttpRequestPtr req, std::string sid);
      drogon::Task<HttpResponsePtr> updateOne(const HttpRequestPtr req, std::string sid);
      drogon::Task<HttpResponsePtr> deleteOne(const HttpRequestPtr req, std::string sid);
      drogon::Task<HttpResponsePtr> get(const HttpRequestPtr req);
      drogon::Task<HttpResponsePtr> create(const HttpRequestPtr req);
    };
  }
}