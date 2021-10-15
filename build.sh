#!/bin/bash

#bootstrap
mkdir src

mkdir build
cd build 


mkdir debug
cd debug
rm -r *
cd ..


mkdir release
cd release 
rm -r *
cd ..

cd ..
cmake -DCMAKE_BUILD_TYPE=Debug -B build/debug
cmake -DCMAKE_BUILD_TYPE=Release -B build/release
#bootstrap

cd build/debug
make -j2 -B

cd ../release
make -j2 -B

