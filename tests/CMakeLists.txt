set(targetName Logger.GTest)

# Get files to build
set(sources
    ${CMAKE_CURRENT_LIST_DIR}/main.gtest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LogEntry.gtest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LogLevel.gtest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LogConfig.gtest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LogOutput.gtest.cpp
    )
    
# Create executable
add_executable(${targetName}
    ${sources}
)

# Link to required libraries
target_link_libraries(${targetName} PUBLIC Logging gtest_main)
set_target_properties(${targetName} PROPERTIES FOLDER "${ideFolderSource}")

# Setup project settings
set_project_warnings(${targetName})  # Which warnings to enable
set_compile_options(${targetName})   # Which extra compiler flags to enable
set_output_directory(${targetName})  # Set the output directory of the library
