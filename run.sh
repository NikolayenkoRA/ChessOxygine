#!/usr/bin/env sh

mkdir build
cd build

#generate cmake project in the "build" folder
cmake ..

#build it
make

#run executable
./Chess
