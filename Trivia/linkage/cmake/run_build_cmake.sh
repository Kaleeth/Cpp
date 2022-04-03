#!/bin/bash
if [ ! -f ./CMakeLists.txt ]; then
	echo "No cmake file!"
	exit 1
fi
if [ ! -d ./build/ ]; then
	mkdir build
fi
cd build
cmake ..
cmake --build .
cd ..
