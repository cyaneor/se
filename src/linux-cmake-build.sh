#!/bin/bash

# Check if the mode (Debug or Release) is provided as a parameter
if [ -z "$1" ]; then
    echo "No build type specified. Please use 'debug' or 'release'."
    echo "Usage: ./build.sh [debug|release]"
    exit 1
fi

# Set the project directory path
PROJECT_DIR=$(pwd)

# Set the build directory based on the input parameter (debug or release)
BUILD_DIR="$PROJECT_DIR/cmake-build-$1"

# Delete the build directory if it exists
if [ -d "$BUILD_DIR" ]; then
    echo "Deleting the existing build directory..."
    rm -rf "$BUILD_DIR"
fi

# Create the build directory
echo "Creating the build directory..."
mkdir "$BUILD_DIR"

# Change to the build directory
cd "$BUILD_DIR" || exit

# Run CMake with the necessary parameters based on the selected mode (debug or release)
echo "Running CMake for $1..."
cmake .. -DCMAKE_BUILD_TYPE="$1"

# Build the project
echo "Building the project..."
make

# Done
echo "Build completed in $1 mode."
