## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
# CMake version
cmake_minimum_required(VERSION 3.0...3.60)

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
# Define Project:
project(win-unix-server-client VERSION 0.1)
	
## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
# Define Source Files to be included 
# in the project :
file(GLOB SOURCE_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/Networking/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/Networking/*.cpp"
)

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
# Set IncludeDirs:
set(PROJECT_INCLUDE_DIRS
		"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
# Add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})		

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
# (Set as Start Project for Visual Studio Solution)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
# Specify the C++ standard # set c++ standard 17 for compatibility
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)	

## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##
# Project Includes Directories
target_include_directories(
	${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIRS})