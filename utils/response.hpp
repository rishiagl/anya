#pragma once

#include <drogon/HttpResponse.h>

namespace response
{
    drogon::HttpResponsePtr newResponse(drogon::HttpStatusCode httpStatusCode, const std::string msg);

    drogon::HttpResponsePtr newResponse(drogon::HttpStatusCode httpStatusCode, const std::string msg, drogon::ContentType contentType, const std::string body);
}