#pragma once

#include <drogon/HttpController.h>
using namespace drogon;
namespace rest
{
  namespace api
  {
    class brand : public drogon::HttpController<brand>
    {
    public:
      METHOD_LIST_BEGIN

      METHOD_ADD(brand::get, "", Get, Options);
      METHOD_ADD(brand::create, "", Post, Options);
      METHOD_ADD(brand::getOne, "/{sid}", Get, Options);
      METHOD_ADD(brand::updateOne, "/{sid}", Put, Options);
      METHOD_ADD(brand::deleteOne, "/{sid}", Delete, Options);

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
