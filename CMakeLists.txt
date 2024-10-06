cmake_minimum_required(VERSION 3.5)

project(LoggingProject)
set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTS "Create the unit tests for the project." True)
option(BUILD_EXAMPLES "Create examples for the project." True)


# Setup project settings
add_subdirectory(lib)

add_subdirectory(src)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()