#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include <map>

class HTTPRequest
{
public:
    std::string method, filepath, query;
    // Headers, not using map because it's behaving weirdly
    std::map<std::string, std::string> headers;
    std::string body;
    bool valid;

    HTTPRequest(char* request, int requestSize);
};

#endif