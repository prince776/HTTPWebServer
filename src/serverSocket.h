#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

/**
 * Creates a TCP Server Socket for listening
 */
class ServerSocket
{
private:
    int socketID;
    sockaddr_in address;
    int addressLen = sizeof(address);

public:
    ServerSocket(int port);
    int acceptConnection();
    int getRequest(int clientID, char* request);
    void sendResponse(int clientID, char* response, int responseSize = -1);
    void closeConnection(int clientID);
    void log(const std::string& message);

    ~ServerSocket();
};

#endif