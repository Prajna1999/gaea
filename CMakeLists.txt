cmake_minimum_required(VERSION 3.10)
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
add_subdirectory(tests)
