# Settings
include(FetchGTest.cmake)
set(targetName Logger.GTest)

# Get files to build
set(sources
    ${CMAKE_CURRENT_LIST_DIR}/main.gtest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LogOutput.gtest.cpp
    )
set(headers )

include_directories("../src/")

# Create executable
add_executable(${targetName}
    ${sources}
    ${headers}
)

# Link to required libraries
target_link_libraries(${targetName} PUBLIC Logger gtest_main)
set_target_properties(${targetName} PROPERTIES FOLDER "${ideFolderSource}")

# Setup project settings
set_project_warnings(${targetName})  # Which warnings to enable
set_compile_options(${targetName})   # Which extra compiler flags to enable
set_output_directory(${targetName})  # Set the output directory of the library

# Add tests
add_test(NAME ${targetName} COMMAND tests)
