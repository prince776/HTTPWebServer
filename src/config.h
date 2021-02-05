#ifndef CONFIG_H
#define CONFIG_H

#include <string>

const std::string ENTRYPOINT = "index.html";
const std::string HEADER = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
// char RESPONSE404[] = "HTTP/1.1 404 Not Found\nContent-Type: text/html\nContent-Length: 35\n\n<html><body>Not found</body></html>";
// size_t RESPONSE404_LENGTH = strlen(RESPONSE404);

constexpr int PORT = 8080;
constexpr int MAXCONN = 10;
constexpr int RESPONSE_SIZE = 4096;
constexpr int REQUEST_SIZE = 4096;
constexpr int CONTENT_SIZE = 4096;

#endif