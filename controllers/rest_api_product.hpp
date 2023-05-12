#pragma once

#include <drogon/HttpController.h>
using namespace drogon;
namespace rest
{
  namespace api
  {
    class product : public drogon::HttpController<product>
    {
    public:
      METHOD_LIST_BEGIN

      METHOD_ADD(product::get, "", Get, Options);
      METHOD_ADD(product::create, "", Post, Options);
      METHOD_ADD(product::getOne, "/{sid}", Get, Options);
      METHOD_ADD(product::updateOne, "/{sid}", Put, Options);
      METHOD_ADD(product::deleteOne, "/{sid}", Delete, Options);

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
