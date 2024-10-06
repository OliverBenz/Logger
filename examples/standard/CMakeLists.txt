cmake_minimum_required(VERSION 3.5)

set(targetName Example.Standard)

# Create executable
add_executable(${targetName}
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

# Link to required libraries
target_link_libraries(${targetName} PUBLIC Logging)
set_target_properties(${targetName} PROPERTIES FOLDER "${ideFolderExamples}")

# Setup project settings
set_project_warnings(${targetName})  # Which warnings to enable
set_compile_options(${targetName})   # Which extra compiler flags to enable
set_output_directory(${targetName})  # Set the output directory of the library
