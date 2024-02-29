cmake_minimum_required(VERSION 3.5)

project(int VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_INSTALL_PREFIX}/include/vtk-9.3/)

# Add the directory containing libfoo.dylib or static.a to the library search path
# link_directories(/usr/local/lib)

############################################################
# Find a dynamic library
############################################################

# find_library(FOO_LIBRARY NAMES foo)
# add_library(foo SHARED IMPORTED)
# set_property(TARGET foo PROPERTY IMPORTED_LOCATION "${FOO_LIBRARY}")

############################################################
# Find a static library
############################################################

add_library(foo_static STATIC IMPORTED)
set_target_properties(foo_static PROPERTIES IMPORTED_LOCATION ${CMAKE_INSTALL_PREFIX}/lib/libfoo_static.a)

include_directories(${VTK_INCLUDE_DIRS})

############################################################
# Include directories for linking to heades
############################################################

# Add the include directory containing foo/exec.h to the include search path
include_directories(${CMAKE_INSTALL_PREFIX}/include
${VTK_INCLUDE_DIRS}
)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(int
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(int SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(int
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(int PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    # foo  # Link against the FooBar::foo library
    foo_static
      # Link against the FooBar library
)

# Set target properties
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.int)
endif()

set_target_properties(int PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS int
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(int)
endif()
