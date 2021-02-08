// Server side C program to demonstrate HTTP Server programming
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>  

#include "config.h"
#include "helper.h"
#include "serverSocket.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"

using namespace std;

HTTPResponse get404Response();
HTTPResponse processHtml(HTTPRequest &req);
HTTPResponse processCSS(HTTPRequest &req);
HTTPResponse processJS(HTTPRequest &req);
HTTPResponse processPhp(HTTPRequest& req);
void serveFile(ServerSocket &server, HTTPRequest& req, int client);

int main(int argc, char const *argv[])
{
	ServerSocket server(PORT);
    server.log(string("Listening on port: ") + to_string(PORT));
    while (true)
    {
		int client = server.acceptConnection();
		if (client < 0) continue;

        char requestBuffer[REQUEST_SIZE] = {0};
        int requestSize = server.getRequest(client, requestBuffer);

        HTTPRequest request(requestBuffer, requestSize);
        
        if (!request.valid)
        {
            server.log("Invalid request");
            server.closeConnection(client);
            continue;
        }

        server.log("REQUEST: " + request.method + " " + request.filepath + " " + request.query);
        serveFile(server, request, client);
		server.closeConnection(client);
    }
    
    return 0;
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
    setenv("GATEWAY_INTERFACE", "CGI/1.1", 1);
    setenv("REDIRECT_STATUS", "200", 1);

    setenv("REQUEST_METHOD", req.method.c_str(), 1);
    setenv("SCRIPT_FILENAME", req.filepath.c_str(), 1);
    setenv("QUERY_STRING", req.query.c_str(), 1);

    if (req.headers.find("Content-Length") != req.headers.end())
    {
        setenv("CONTENT_TYPE", req.headers["Content-Type"].c_str(), 1);
        setenv("CONTENT_LENGTH", req.headers["Content-Length"].c_str(), 1);
        writeFile("input.txt", req.body);
    }

    string output = exec("php-cgi < input.txt");
    output = output.substr(output.find_first_of('\n'));

    return HTTPResponse(200, "OK", "text/html", output);
}
