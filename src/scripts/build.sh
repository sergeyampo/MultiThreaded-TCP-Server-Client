#!/bin/bash
cd ../
cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" -B./build -H./
cmake --build ./build -- -j4