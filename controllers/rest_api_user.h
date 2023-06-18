#pragma once

#include <drogon/HttpController.h>
using namespace drogon;

class user : public drogon::HttpController<user>
{
public:
  METHOD_LIST_BEGIN
  // use METHOD_ADD to add your custom processing function here;
  METHOD_ADD(user::getUserNames, "", Get, Options);
  METHOD_ADD(user::signup, "/signup", Post, Options);
  METHOD_ADD(user::signin, "/signin", Post, Options);
  METHOD_ADD(user::regenerateKey, "/regenerateKey", Post, Options);
  METHOD_LIST_END

  drogon::Task<drogon::HttpResponsePtr> getUserNames(const HttpRequestPtr req);

  drogon::Task<drogon::HttpResponsePtr> signup(const HttpRequestPtr req);

  drogon::Task<drogon::HttpResponsePtr> signin(const HttpRequestPtr req);
};
