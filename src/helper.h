#ifndef HELPER_H
#define HELPER_H

#include <string>

void closeProgram(const std::string& message, int exitCode);
std::string readFile(const std::string& file);

#endif