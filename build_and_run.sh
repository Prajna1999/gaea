#!/bin/bash

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

print_color() {
    printf "${2}${1}${NC}\n"
}

if [ ! -f "CMakeLists.txt" ]; then
    print_color "Error: CMakeLists.txt not found. Are you in the project root?" "$RED"
    exit 1
fi

print_color "Setting up build directory..." "$YELLOW"
rm -rf build
mkdir build
cd build

print_color "Configuring the project..." "$YELLOW"
cmake .. 

print_color "Building the project..." "$YELLOW"
make 

print_color "Running tests..." "$YELLOW"
ctest --output-on-failure

print_color "Running Gaea..." "$YELLOW"
./gaea

print_color "Done!" "$GREEN"