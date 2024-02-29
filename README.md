# Description

This repository provides a skeleton for a CMake project structure, demonstrating best practices for organizing a C++ project with multiple sub-libraries, binaries, unit tests, and 3rd party library imports. It serves as a starting point for new C++ projects, showcasing how to efficiently manage dependencies, build configurations, and testing workflows using CMake.

## Features:

Modular project structure with separate directories for libraries, executables, and unit tests.
Integration of CMake's add_subdirectory() feature for managing multiple sub-libraries.
Configuration for building and installing the project using CMake.
Integration of third-party libraries using CMake's find_package() or FetchContent functionality.
Setup of unit testing using CMake's add_test() and integration with popular testing frameworks.
Example configurations for building the project on various platforms, including Linux, macOS, and Windows.

## Usage:

To build and install the project:

```bash
mkdir build
cd build
cmake ..
cmake --build .
cmake --install .
```

To run unit tests:

```bash
Copy code
cd build
ctest
```

## License:

This project is licensed under the MIT License.
