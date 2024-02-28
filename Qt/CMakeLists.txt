# Set the project name
project (MudRockQtComponents)

# Add a library with the above sources
add_library(${PROJECT_NAME} src/TestWidget.cpp)

add_library(MudRock::QtComponents ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
