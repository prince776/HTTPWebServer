#ifndef CONFIG_H
#define CONFIG_H

#include <string>

const std::string ENTRYPOINT = "index.php";

constexpr int PORT = 8080;
constexpr int MAXCONN = 10;
constexpr int RESPONSE_SIZE = 4096;
constexpr int REQUEST_SIZE = 4096;
constexpr int CONTENT_SIZE = 4096;
constexpr int THREADPOOL_SIZE = 8;

#endif