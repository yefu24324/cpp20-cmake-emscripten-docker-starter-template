cmake_minimum_required(VERSION 3.16...3.29 FATAL_ERROR)
project(
	my_project
	VERSION 1.0.0
	LANGUAGES CXX C
)

#######################################
# Utils

include(cmake/TargetProperties.cmake)

#######################################
# Target definitions

add_subdirectory(src)

# Set 'my_project' as the default target in the generated Visual Studio solution
set_property(
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	PROPERTY VS_STARTUP_PROJECT my_project
)

