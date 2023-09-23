[ -d "build" ] || mkdir build

zig c++ src/main.cpp -o "$1/$2"
