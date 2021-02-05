#include "serverSocket.h"

#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include "helper.h"
#include "config.h"

ServerSocket::ServerSocket(int port)
{
    socketID = socket(AF_INET, SOCK_STREAM, 0);
    if (socketID == 0) closeProgram("Error in server creation", EXIT_FAILURE);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    memset(address.sin_zero, 0, sizeof(address.sin_zero));

    if (bind(socketID, (sockaddr*)&address, sizeof(address)) < 0)
        closeProgram("Error in binding server socket", EXIT_FAILURE);
    
    if (listen(socketID, MAXCONN) < 0)
        closeProgram("Failed to listen", EXIT_FAILURE);
}

int ServerSocket::acceptConnection()
{
    return accept(socketID, (struct sockaddr *)&address, (socklen_t*)&addressLen);
}

int ServerSocket::getRequest(int clientID, char* request)
{
    return read(clientID, request, REQUEST_SIZE);
}

void ServerSocket::sendResponse(int clientID, char* response, int responseSize)
{
    if (responseSize < 0) responseSize = strlen(response);
    if (responseSize <= 0) return;
    write(clientID, response, responseSize);
}

void ServerSocket::closeConnection(int clientID)
{
    close(clientID);
}

void ServerSocket::log(const std::string &message)
{
    std::cout << "[Server] " << message << "\n";
}
