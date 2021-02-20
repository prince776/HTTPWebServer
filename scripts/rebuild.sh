#!/bin/bash
cd ../build

if [ -n "$1" ]; then 
	cmake .. $1
else
    cmake ..
fi

make
cd bin/
./HTTPWebServer