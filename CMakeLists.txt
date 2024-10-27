# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Stringer VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include src)  # Add both 'include' and 'src' directories

# Find all .cpp files in the src directory and add them to the executable
file(GLOB SRC_FILES src/*.cpp)

# Add the executable
set(ASSETS_PATH "${CMAKE_SOURCE_DIR}/assets")
add_executable(Stringer src/main.cpp src/Stopwatch.cpp src/Image.cpp)
target_compile_definitions(Stringer PRIVATE ASSETS_PATH="${ASSETS_PATH}")