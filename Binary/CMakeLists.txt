project(subbinary)

# Create the executable
add_executable(${PROJECT_NAME} main.cpp)

# Link using project aliases

target_link_libraries(${PROJECT_NAME}
	MudRock::QtComponents
	MudRock::Utils

)
