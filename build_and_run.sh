#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to print colored output
print_color() {
    printf "${2}${1}${NC}\n"
}

# Ensure we're in the project root
if [ ! -d "build" ]; then
    print_color "Error: 'build' directory not found. Are you in the project root?" "$RED"
    exit 1
fi

# Navigate to build directory
cd build

# Rebuild the project
print_color "Rebuilding the project..." "$YELLOW"
cmake ..
make

# Run tests
print_color "Running tests..." "$YELLOW"
ctest

# Run the main executable
print_color "Running Gaea..." "$YELLOW"
./gaea

print_color "Done!" "$GREEN"