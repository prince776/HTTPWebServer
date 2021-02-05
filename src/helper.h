#ifndef HELPER_H
#define HELPER_H

#include <string>

void closeProgram(const std::string& message, int exitCode);
std::pair<std::string, bool> readFile(const std::string& file);

#endif