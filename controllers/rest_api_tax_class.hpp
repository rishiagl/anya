#pragma once

#include <drogon/HttpController.h>
using namespace drogon;
namespace rest
{
  namespace api
  {
    class tax_class : public drogon::HttpController<tax_class>
    {
    public:
      METHOD_LIST_BEGIN

      METHOD_ADD(tax_class::get, "", Get, Options);
      METHOD_ADD(tax_class::create, "", Post, Options);
      METHOD_ADD(tax_class::getOne, "/{1}", Get, Options);
      METHOD_ADD(tax_class::updateOne, "/{1}", Put, Options);
      METHOD_ADD(tax_class::deleteOne, "/{1}", Delete, Options);

      METHOD_LIST_END

      void getOne(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback,
                  int &&code);
      void updateOne(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     int &&code);
      void deleteOne(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback,
                     int &&code);
      void get(const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback);
      void create(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback);
    };
  }
}
