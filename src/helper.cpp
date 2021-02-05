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

std::pair<std::string, bool> readFile(const std::string& file)
{
	std::ifstream in(file);
	std::string res = "";
	bool exists = false;
	if (in.is_open())
	{
		exists = true;
		res = { std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>() };
	}
	return std::make_pair(res, exists);
}