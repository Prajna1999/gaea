cmake_minimum_required(VERSION 3.10)
project(Gaea VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(include)

# Create the library
add_library(gaea_lib STATIC src/gaea.c)

# Create the main executable
add_executable(gaea src/main.c)
target_link_libraries(gaea gaea_lib)

# CLI executable
add_executable(gaea_cli src/gaea_cli.c)
target_link_libraries(gaea_cli PRIVATE gaea_lib)



# Create the test executable
add_executable(test_gaea_types tests/test_gaea_types.c)
target_link_libraries(test_gaea_types gaea_lib)

# Enable compiler warnings
target_compile_options(gaea PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(test_gaea_types PRIVATE -Wall -Wextra -Wpedantic)
# Set compiler warnings for the CLI
target_compile_options(gaea_cli PRIVATE -Wall -Wextra -Wpedantic)

enable_testing()
add_test(NAME test_gaea_types COMMAND test_gaea_types)
