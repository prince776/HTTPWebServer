#ifndef HELPER_H
#define HELPER_H

#include <string>

bool fileExists(const std::string& file);
std::pair<std::string, bool> readFile(const std::string& file);
void writeFile(const std::string& file, const std::string& content);

void closeProgram(const std::string& message, int exitCode);
std::string exec(const char* cmd);

#endif