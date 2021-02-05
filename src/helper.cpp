#include <iostream>
#include <string>

#include "helper.h"

void closeProgram(const std::string& message, int exitCode)
{
    std::cerr << message;
    exit(exitCode);
} 