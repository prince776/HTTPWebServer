#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>


#include "helper.h"

void closeProgram(const std::string& message, int exitCode)
{
    std::cerr << message;
    exit(exitCode);
}

std::string readFile(const std::string& file)
{
	std::ifstream in(file);
	if (in.is_open())
		return { std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>() };
	return "";
}