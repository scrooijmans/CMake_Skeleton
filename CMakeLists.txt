cmake_minimum_required(VERSION 3.14)
project(MudRock)

# add_subdirectory(source)
add_subdirectory(Binary)
add_subdirectory(Utils)
add_subdirectory(Qt)

option(BUILD_TEST "" ON)
option(BUILD_EXAMPLES "Whether to include examples" ON)

set(CMAKE_CXX_STANDARD 17)


############################################################
# Find 3rd Party packages
############################################################

# find_package(Qt NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(VTK REQUIRED)

# check if lib was found
if(VTK_FOUND)
    message ("VTK found")
else()
    message (FATAL_ERROR "Cannot find VTK")
endif()

############################################################
# Create a library
############################################################

# # Static
# add_library(MudRock STATIC
#     src/Hello.cpp
# )

# Shared lib
# add_library (MudRock SHARED
#     src/Function.cpp
#     src/utils.cpp
# )
# add_library(MudRock::libary ALIAS MudRock)

# target_include_directories(MudRock
#     PUBLIC
#     ${PROJECT_SOURCE_DIR}/include
# )


############################################################
# Create executable
############################################################

# add_executable(MudRock_bin
#     src/main.cpp
# )

# # link the library target with the binary target
# target_link_libraries(MudRock_bin
#     PRIVATE
#     MudRock
#     Qt${QT_VERSION_MAJOR}::Widgets
#     ${VTK_LIBRARIES}
# )

############################################################
# Build examples and tests
############################################################

# if(BUILD_EXAMPLES)
#     message(STATUS "Building examples..")
#     add_subdirectory(examples)
# endif()

# if(BUILD_TEST)
#     message(STATUS "Testing...")
#     add_subdirectory(tests)
# endif()

############################################################
# Install binaries and libraries
############################################################

# # Binaries
# install (TARGETS MudRock_bin
#     DESTINATION bin)

# # Library
# install (TARGETS MudRock
#     LIBRARY DESTINATION lib
# )

# # Header files
# install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
#     DESTINATION include
# )

# # Config
# install (FILES cmake-examples.conf
#     DESTINATION etc
# )

