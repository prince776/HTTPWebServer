// Server side C program to demonstrate HTTP Server programming
#include <iostream>
#include <string>
#include <cstring>

#include "config.h"
#include "serverSocket.h"

using namespace std;

int main(int argc, char const *argv[])
{
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
	
	ServerSocket server(PORT);

    while (true)
    {
        cout << "\n+++++++ Waiting for new connection ++++++++\n\n";

		int client = server.acceptConnection();
		if (client < 0) continue;

        char request[REQUEST_SIZE] = {0};
        int requestSize = server.getRequest(client, request);

        cout << request << "\n";

		server.sendResponse(client, hello);
        cout << "------------------Hello message sent-------------------";
		server.closeConnection(client);
    }
    return 0;
}