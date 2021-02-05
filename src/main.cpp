// Server side C program to demonstrate HTTP Server programming
#include <iostream>
#include <string>
#include <cstring>

#include "config.h"
#include "serverSocket.h"
#include "HTTPResponse.h"

using namespace std;

int main(int argc, char const *argv[])
{
	ServerSocket server(PORT);
    server.log(string("Listening on port: ") + to_string(PORT));
    while (true)
    {
		int client = server.acceptConnection();
		if (client < 0) continue;

        char request[REQUEST_SIZE] = {0};
        int requestSize = server.getRequest(client, request);

        // Process request        
        
        // Generate response
        
        HTTPResponse response(200, "OK", "text/html", "Test Page");
		server.sendResponse(client, response.response, response.responseSize);
		server.closeConnection(client);
    }
    return 0;
}