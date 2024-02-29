cmake_minimum_required(VERSION 3.5)

project(Foo VERSION 1.0 LANGUAGES CXX)

# Find VTK package
find_package(VTK REQUIRED)

# Include VTK headers
include_directories(${CMAKE_INSTALL_PREFIX}/include/vtk-9.3/)

configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)

add_library(foo SHARED config.h.in
    exec.h exec.cpp)
# Alias the foo library under FooBar namespace

# Static library
add_library(foo_static STATIC
    exec.h
    exec.cpp
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"  # Include generated config.h
)

add_library(FooBar::foo ALIAS foo)
# Alias for static library under FooBar namespace
add_library(FooBar::foo_static ALIAS foo_static)

set_target_properties(foo PROPERTIES
  PUBLIC_HEADER "exec.h;${CMAKE_CURRENT_BINARY_DIR}/config.h"
  MACOSX_RPATH TRUE
)

# Set properties for static library
set_target_properties(foo_static PROPERTIES
    PUBLIC_HEADER "exec.h;${CMAKE_CURRENT_BINARY_DIR}/config.h"
)

# Link the VTK library to foo
target_link_libraries(foo PRIVATE ${VTK_LIBRARIES})

# Link the VTK library to foo
target_link_libraries(foo_static PRIVATE ${VTK_LIBRARIES})

install(TARGETS foo
  # IMPORTANT: Add the foo library to the "export-set"
  EXPORT FooBarTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/foo"
    COMPONENT dev
)

# Install static library
install(TARGETS foo_static
    EXPORT FooBarTargets
    ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT lib
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/foo" COMPONENT dev
)

