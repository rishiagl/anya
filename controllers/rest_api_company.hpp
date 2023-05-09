#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace rest
{
  namespace api
  {
    class company : public drogon::HttpController<company>
    {
    public:
      METHOD_LIST_BEGIN
      // use METHOD_ADD to add your custom processing function here;
      METHOD_ADD(company::get, "/", Get);
      METHOD_ADD(company::add, "/", Post);
      METHOD_ADD(company::getById, "/{cid}", Get); // path is /rest/api/company/{arg2}/{arg1}
      // ADD_METHOD_VIA_REGEX(company::getById, "rest/api/company/.*(C23_[0-9])", Get);
      //  METHOD_ADD(company::your_method_name, "/{1}/{2}/list", Get); // path is /rest/api/company/{arg1}/{arg2}/list
      //  ADD_METHOD_TO(company::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list

      METHOD_LIST_END
      // your declaration of processing function maybe like this:
      void get(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
      void add(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
      void getById(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string cid);
      // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    };
  }
}
