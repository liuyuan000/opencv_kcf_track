#!/usr/bin/env bash
cd build
cmake ..
make
cd ../bin
./kcf
