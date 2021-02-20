#!/bin/bash
cd ..
cd build

if [ -n "$1" ]; then 
	cmake .. $1
else
    cmake ..
fi

make
cd bin/
./HTTPWebServer