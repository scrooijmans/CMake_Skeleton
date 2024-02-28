# Set the project name
project (MudRockUtils)

option(BUILD_TEST "" ON)

# Add a library with the above sources
add_library(${PROJECT_NAME} src/Utils.cpp)

add_library(MudRock::Utils ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

if(BUILD_TEST)
	message(STATUS "Testing..")
	add_subdirectory(tests)
endif()