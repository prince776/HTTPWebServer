#include "HTTPResponse.h"

#include <string>
#include <sstream>
#include <cstring>

#include "config.h"

HTTPResponse::HTTPResponse(int statusCode, const std::string& status, const std::string& contentType, const std::string& content)
    : statusCode(statusCode), status(status), contentType(contentType)
{
    this->response = new char[RESPONSE_SIZE];
    responseSize = 0;

    std::stringstream ss;
    ss << "HTTP/1.1 ";
    ss << std::to_string(statusCode) << " ";
    ss << status << "\n";
    ss << "Content-Type: " << contentType << "\n";
    ss << "Content-Length: " << std::to_string(content.size()) << "\n\n";

    std::string header = ss.str();    
    for (int i = 0; i < header.size(); i++)
        response[responseSize++] = header[i];
    for (int i = 0; i < content.size(); i++)
        response[responseSize++] = content[i];
}
