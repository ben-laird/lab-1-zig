[ -d "build" ] || mkdir build

zig c++ src/main.cpp -o ./build/lab-1-build
