#!/bin/bash

# Gaea Database Project Setup Script

set -e  # Exit immediately if a command exits with a non-zero status.

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to print colored output
print_color() {
    printf "${2}${1}${NC}\n"
}

# Function to check if a command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Check for required commands
required_commands=("cmake" "gcc")
for cmd in "${required_commands[@]}"; do
    if ! command_exists "$cmd"; then
        print_color "Error: $cmd is not installed. Please install it and run this script again." "$RED"
        exit 1
    fi
done

# Create project structure
print_color "Creating project structure..." "$YELLOW"
mkdir -p src include tests docs build

# Create initial source files
print_color "Creating initial source files..." "$YELLOW"
echo "#include <stdio.h>
#include \"gaea.h\"

int main() {
    printf(\"Welcome to Gaea Database!\\n\");
    return 0;
}" > src/main.c

echo "#ifndef GAEA_H
#define GAEA_H

// Gaea database function declarations will go here

#endif // GAEA_H" > include/gaea.h

# Create CMakeLists.txt
print_color "Creating CMakeLists.txt..." "$YELLOW"
echo "cmake_minimum_required(VERSION 3.10)
project(Gaea VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add include directory
include_directories(include)

# Add executable
add_executable(gaea src/main.c)

# Enable compiler warnings
target_compile_options(gaea PRIVATE -Wall -Wextra -Wpedantic)

# Add tests
enable_testing()
add_subdirectory(tests)" > CMakeLists.txt

# Create test files
print_color "Creating test files..." "$YELLOW"
mkdir -p tests
echo "#include <assert.h>
#include \"gaea.h\"

int main() {
    // Your tests will go here
    return 0;
}" > tests/test_gaea.c

echo "add_executable(test_gaea test_gaea.c)
add_test(NAME test_gaea COMMAND test_gaea)" > tests/CMakeLists.txt

# Update .gitignore if it doesn't exist
if [ ! -f .gitignore ]; then
    print_color "Creating .gitignore..." "$YELLOW"
    echo "build/
*.o
*.out
.vscode/
.idea/
*.swp
*~" > .gitignore
fi

# Initialize CMake
print_color "Initializing CMake..." "$YELLOW"
mkdir -p build && cd build
cmake ..

# Build the project
print_color "Building the project..." "$YELLOW"
make

# Run tests
print_color "Running tests..." "$YELLOW"
ctest

# Final message
print_color "Gaea project setup complete!" "$GREEN"
print_color "Next steps:" "$YELLOW"
print_color "1. Review and edit the source files in the src/ and include/ directories." "$YELLOW"
print_color "2. Add more tests in the tests/ directory." "$YELLOW"
print_color "3. Use 'git add' and 'git commit' to start version controlling your changes." "$YELLOW"
print_color "4. Happy coding!" "$GREEN"