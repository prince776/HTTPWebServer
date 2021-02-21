cmake_minimum_required(VERSION 3.9.1)

project(HTTPWebServer)

option(USE_PHP_FPM "Use PHP FPM" OFF)

if (USE_PHP_FPM)
	add_definitions(-DUSE_PHP_FPM=1)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

set(SOURCES 	src/main.cpp
				src/serverSocket.cpp
				src/HTTPRequest.cpp
				src/HTTPResponse.cpp
				src/helper.cpp
)

add_executable(HTTPWebServer ${SOURCES})

target_link_libraries(HTTPWebServer pthread)
