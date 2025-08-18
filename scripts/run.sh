# !/bin/sh
set -ex 

cmake -S . -B build
cmake --build build
./build/eternal_dreamweaver
