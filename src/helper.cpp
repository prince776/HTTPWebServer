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

int readFile(const std::string& file, char* buffer)
{
	int ptr = -1;
	char c;
	std::ifstream in(file);
	if (in.is_open())
	{
		ptr = 0;
		std::string content = { std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>() };
		for (int i = 0; i < content.size(); i++)
			buffer[ptr++] = content[i];
	}
	return ptr;
}