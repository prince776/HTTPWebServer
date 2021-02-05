// Server side C program to demonstrate HTTP Server programming
#include <iostream>
#include <string>
#include <cstring>

#include "config.h"
#include "helper.h"
#include "serverSocket.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"

using namespace std;

void serve404(ServerSocket&server, int client);
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

        // Process request        
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
    string fileType = req.filepath.substr(req.filepath.find_last_of('.') + 1);
    if (fileType == "html")
    {
        server.log("Reading " + req.filepath);
        auto [htmlContent, exists] = readFile(req.filepath);
        server.log(htmlContent);

        if (!exists) return serve404(server, client);

        HTTPResponse res(200, "OK", "text/html", htmlContent);
        server.sendResponse(client, res.response, res.responseSize);
    }else
    {
        serve404(server, client);
    }
}

void serve404(ServerSocket&server, int client)
{
    HTTPResponse res(404, "Not Found", "text/html", "Page Not Found");
    server.sendResponse(client, res.response, res.responseSize);
}
