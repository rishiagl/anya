#pragma once

#include <drogon/HttpController.h>

using namespace drogon;
namespace rest
{
  namespace api
  {
    class product_category : public drogon::HttpController<product_category>
    {
    public:
      METHOD_LIST_BEGIN

      METHOD_ADD(product_category::get, "", Get, Options);
      METHOD_ADD(product_category::create, "", Post, Options);
      METHOD_ADD(product_category::getOne, "/{sid}", Get, Options);
      METHOD_ADD(product_category::updateOne, "/{sid}", Put, Options);
      METHOD_ADD(product_category::deleteOne, "/{sid}", Delete, Options);

      METHOD_LIST_END

      void getOne(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback,
                  std::string &&sid);
      void updateOne(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string &&sid);
      void deleteOne(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string &&sid);
      void get(const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback);
      void create(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback);
    };
  }
}
