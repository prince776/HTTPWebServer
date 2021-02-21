#!/bin/bash
cd ..
cd build

if [ -n "$1" ]; then 
	cmake .. $1
else
    cmake ..
fi
cd bin/
rm HTTPWebServer
cd ..
make
cd bin/
./HTTPWebServer