#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>  
#include <mutex>

#include "config.h"
#include "helper.h"
#include "serverSocket.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "threadPool.h"

using namespace std;

HTTPResponse get404Response();
HTTPResponse processHtml(HTTPRequest &req);
HTTPResponse processCSS(HTTPRequest &req);
HTTPResponse processJS(HTTPRequest &req);
HTTPResponse processPhp(HTTPRequest& req);

void handleConnection(int client, ServerSocket& server);
void serveFile(ServerSocket &server, HTTPRequest& req, int client);

mutex phpInputFileMutex;

int main(int argc, char const *argv[])
{
	ServerSocket server(PORT);
    server.log(string("Listening on port: ") + to_string(PORT));

    ThreadPool<int, THREADPOOL_SIZE> threadPool(handleConnection, server);

    while (true)
    {
		int client = server.acceptConnection();
        if (client < 0) continue;

        threadPool.addTask(client);
    }
    
    return 0;
}

void handleConnection(int client, ServerSocket& server)
{
    if (client <= 0) return;

    char requestBuffer[REQUEST_SIZE] = {0};
    int requestSize = server.getRequest(client, requestBuffer);

    HTTPRequest request(requestBuffer, requestSize);
    
    if (!request.valid)
    {
        server.log("Invalid request");
        server.closeConnection(client);
        return;
    }

    server.log("REQUEST: " + request.method + " " + request.filepath + " " + request.query);
    serveFile(server, request, client);
    server.closeConnection(client); 
}

void serveFile(ServerSocket &server, HTTPRequest& req, int client)
{
    HTTPResponse res = get404Response();

    string fileType = req.filepath.substr(req.filepath.find_last_of('.') + 1);
    bool exists = fileExists(req.filepath);

    if (!exists) ;
    else if (fileType == "html") res = processHtml(req);
    else if (fileType == "php") res = processPhp(req);
    else if (fileType == "css") res = processCSS(req);
    else if (fileType == "js") res = processJS(req);
    
    server.sendResponse(client, res.response, res.responseSize);
    server.log("Response of size: " + to_string(res.responseSize) + " bytes served");
}

HTTPResponse get404Response()
{
    return HTTPResponse(404, "Not Found", "text/html", "Page Not Found");
}

HTTPResponse processHtml(HTTPRequest &req)
{
    return HTTPResponse(200, "OK", "text/html", readFile(req.filepath).first);
}

HTTPResponse processCSS(HTTPRequest &req)
{
    return HTTPResponse(200, "OK", "text/css", readFile(req.filepath).first);
}

HTTPResponse processJS(HTTPRequest &req)
{
    return HTTPResponse(200, "OK", "text/javascript", readFile(req.filepath).first);
}

HTTPResponse processPhp(HTTPRequest& req)
{
    std::string fullPath = exec("pwd");
    fullPath.back() = '/';
    fullPath += req.filepath;

    setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
    setenv("REDIRECT_STATUS", "200", 1);

    setenv("REQUEST_METHOD", req.method.c_str(), 1);
    setenv("SCRIPT_FILENAME", fullPath.c_str(), 1);
    setenv("SCRIPT_NAME", req.filepath.c_str(), 1);
    setenv("QUERY_STRING", req.query.c_str(), 1);

    if (req.headers.find("Content-Length") != req.headers.end())
    {
        setenv("CONTENT_TYPE", req.headers["Content-Type"].c_str(), 1);
        setenv("CONTENT_LENGTH", req.headers["Content-Length"].c_str(), 1);
    }

    string output;
    {
        lock_guard<mutex> guard(phpInputFileMutex);

        writeFile("input.txt", req.body);

        #ifdef USE_PHP_FPM
        output = exec("cgi-fcgi < input.txt -bind -connect /var/run/php/php-fpm.sock");
        #else
        output = exec("php-cgi < input.txt");
        #endif  
    }

    auto pos = output.find("\n");
    string headers = output.substr(0, pos);
    output = output.substr(pos);

    return HTTPResponse(200, "OK", headers, output, true);
}
