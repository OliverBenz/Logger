set(targetName Logger.GTest)
    
add_executable(${targetName}
    "${CMAKE_CURRENT_LIST_DIR}/main.gtest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/LogEntry.gtest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/LogLevel.gtest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/LogConfig.gtest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/LogOutput.gtest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Profiler.gtest.cpp"
)

# Link to required libraries
target_link_libraries(${targetName} PUBLIC Logger::Logger gtest_main)
set_target_properties(${targetName} PROPERTIES FOLDER "${ideFolderTests}")

# Setup project settings
set_project_warnings(${targetName})  # Which warnings to enable
set_compile_options(${targetName})   # Which extra compiler flags to enable
set_output_directory(${targetName})  # Set the output directory of the library

# Add tests
include(GoogleTest)
gtest_discover_tests(${targetName})
