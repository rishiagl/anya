#include <response.hpp>

drogon::HttpResponsePtr response::newResponse(drogon::HttpStatusCode httpStatusCode, const std::string msg)
{
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(httpStatusCode);
    resp->addHeader("message", msg);
    return resp;
}

drogon::HttpResponsePtr response::newResponse(drogon::HttpStatusCode httpStatusCode, const std::string msg, drogon::ContentType contentType, const std::string body)
{
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(httpStatusCode);
    resp->addHeader("message", msg);
    resp->setContentTypeCode(contentType);
    resp->setBody(body);
    return resp;
}