#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>

class HTTPResponse
{
public:
    int statusCode;
    std::string status, contentType;
    char* response;
    int responseSize;

    HTTPResponse(int statusCode, const std::string& status, const std::string& contentType, const std::string& content);
    HTTPResponse(int statusCode, const std::string& status, const std::string& headers, const std::string& content, bool useHeader);
};

#endif