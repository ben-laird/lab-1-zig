[ -d "$1" ] || mkdir "$1"

zig c++ src/main.cpp -o "$1/$2"
