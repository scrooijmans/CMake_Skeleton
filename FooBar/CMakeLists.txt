cmake_minimum_required(VERSION 3.5)
project(FooBar VERSION 0.1 LANGUAGES CXX)

set(FOOBAR_MAJOR_VERSION 0)
set(FOOBAR_MINOR_VERSION 1)
set(FOOBAR_PATCH_VERSION 0)
set(FOOBAR_VERSION
  ${FOOBAR_MAJOR_VERSION}.${FOOBAR_MINOR_VERSION}.${FOOBAR_PATCH_VERSION})

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/FooBar)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

# Make relative paths absolute (needed later on).
# loop ensures that the paths defined by INSTALL_LIB_DIR, INSTALL_BIN_DIR, INSTALL_INCLUDE_DIR,
# and INSTALL_CMAKE_DIR # are absolute paths by prefixing them with the installation prefix #
# if they are not already absolute.

# For each iteration, it constructs a variable name var by concatenating INSTALL_,
# the current value of p, and _DIR. For example, if p is LIB, then var becomes INSTALL_LIB_DIR.
# if(NOT IS_ABSOLUTE "${${var}}"):
# Checks if the value of the variable ${var} (e.g., ${INSTALL_LIB_DIR}) is not an absolute path.
# set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}"): If the path is not absolute,
# it prepends the value of CMAKE_INSTALL_PREFIX (which is typically the installation
# prefix specified by the user or defaults to /usr/local) to the current value of the variable ${var}.
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()
# find_package(VTK REQUIRED)

# set up include-directories
include_directories(
  "${PROJECT_SOURCE_DIR}"   # to find foo/foo.h
  "${PROJECT_BINARY_DIR}"   # to find foo/config.h
  ${VTK_INCLUDE_DIRS}
)

# Add sub-directories
add_subdirectory(foo)
# add_subdirectory(bar)

# The interesting stuff goes here
# ===============================

# Add all targets to the build-tree export set
export(TARGETS foo foo_static
    # bar
  FILE "${PROJECT_BINARY_DIR}/FooBarTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE FooBar)

# Create the FooBarConfig.cmake and FooBarConfigVersion files
# RELATIVE_PATH: variable where the resulting relative path will be stored.
# REL_INCLUDE_DIR will contain the relative path from ${INSTALL_CMAKE_DIR} to ${INSTALL_INCLUDE_DIR}.
# ${INSTALL_CMAKE_DIR} is the directory from which you want to calculate the relative path.
# ${INSTALL_INCLUDE_DIR} is the directory to which you want to calculate the relative path.
# file(RELATIVE_PATH <variable> <directory> <base-directory>)
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(FooBarConfig.cmake.in
  "${PROJECT_BINARY_DIR}/FooBarConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${FOOBAR_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(FooBarConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/FooBarConfig.cmake" @ONLY)
# ... for both
configure_file(FooBarConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/FooBarConfigVersion.cmake" @ONLY)

# Install the FooBarConfig.cmake and FooBarConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/FooBarConfig.cmake"
  "${PROJECT_BINARY_DIR}/FooBarConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

# Install the export set for use with the install-tree
install(EXPORT FooBarTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
