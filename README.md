# CMake_Skeleton
Skeleton for a CMake project structure, demonstrating best practices for organizing a C++ project with multiple sub-libraries, binaries, unit tests, and 3rd party library imports. Showcases how to efficiently manage dependencies, build configurations, and testing workflows using CMake.


## Features

- Modular project structure with separate directories for libraries, executables, and unit tests.
- Integration of CMake's `add_subdirectory()` feature for managing multiple sub-libraries.
- Configuration for building and installing the project using CMake.
- Integration of third-party libraries using CMake's `find_package()` or `FetchContent` functionality.
- Setup of unit testing using CMake's `add_test()` and integration with popular testing frameworks.
- Example configurations for building the project on various platforms, including Linux, macOS, and Windows.

## Usage

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
cd build
ctest
```

For more detailed instructions and customization options, please refer to the README file and the CMakeLists.txt files within each directory.

## License
This project is licensed under the MIT License.
