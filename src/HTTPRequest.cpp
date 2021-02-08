#include "HTTPRequest.h"

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstring>

#include "config.h"

HTTPRequest::HTTPRequest(char* request, int requestSize)
{
    std::stringstream firstLineSS;
    int i = 0;
    for (i = 0; i < requestSize; i++)
    {
        if (request[i] == '\n' || request[i] == 0) break;
        firstLineSS << request[i];
    }
    std::string firstLine = firstLineSS.str();
    if (firstLine.find("HTTP/1.1") == std::string::npos)
    {
        valid = false;
        return;
    }
    std::vector<std::string> words;
    for (std::string word; firstLineSS >> word;)
        words.push_back(word);
    
    method = words[0];
    filepath = words[1];

    auto pos = filepath.find("?");
    if (pos != std::string::npos)
    {
        query = filepath.substr(pos + 1);
        filepath = filepath.substr(0, pos);
    }
    else query = "";
    filepath = filepath.substr(1);
    if (filepath == "") filepath = ENTRYPOINT;
    
    std::stringstream ss;
    for (; i < requestSize; i++) ss << request[i];
    for (std::string word; ss >> word;)
    {
        if (word.back() != ':') continue;
        std::string header = word.substr(0, word.size() - 1);
        ss >> word;
        headers[header] = word;
    }
    body = "";
    std::string reqStr = ss.str();
    if (headers.find("Content-Length") != headers.end())
        body = reqStr.substr(reqStr.size() - stoi(headers["Content-Length"]));

    valid = true;
}
