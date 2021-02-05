#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>

class HTTPRequest
{
public:
    std::string method, filepath, query;
    bool valid;

    HTTPRequest(char* request, int requestSize);
};

#endif