#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <sys/stat.h>

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
    in.close();
	return std::make_pair(res, exists);
}

bool fileExists(const std::string& file)
{
	struct stat buffer;   
	return (stat (file.c_str(), &buffer) == 0); 
}

void writeFile(const std::string& file, const std::string& content)
{
    std::ofstream out(file);
    out << content;
    out.flush();
    out.close();
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}