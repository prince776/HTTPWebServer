#!/bin/bash
cd ..
rm -rf build #clean previous builds
mkdir build
cd build

if [ -n "$1" ]; then 
	cmake .. $1
else
    cmake ..
fi

make
cd bin
cp ../../public/* .
./HTTPWebServer