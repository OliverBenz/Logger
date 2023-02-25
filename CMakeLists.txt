cmake_minimum_required(VERSION 3.12)

project(Logging)
set(CMAKE_CXX_STANDARD 17)

option(BUILD_TESTS "Create the unit tests for the project." True)
option(BUILD_EXAMPLES "Create examples for the project." True)


# Setup project settings
include(cmake/ProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/CustomCommands.cmake)


add_subdirectory(src)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()