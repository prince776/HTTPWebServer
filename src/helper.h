#ifndef HELPER_H
#define HELPER_H

#include <string>

void closeProgram(const std::string& message, int exitCode);
int readFile(const std::string& file, char* buffer);

#endif