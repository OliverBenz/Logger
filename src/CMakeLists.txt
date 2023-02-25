find_package(Threads)

# Settings
set(targetName Logger)

# Get files to build
file(GLOB headers CONFIGURE_DEPENDS "*.hpp")
file(GLOB sources CONFIGURE_DEPENDS "*.cpp")

# Create executable
add_library(${targetName} STATIC
    # Common modules
    ${headers}
    ${sources}
)

# Link to thread module.
target_link_libraries(${targetName} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(${targetName} PROPERTIES FOLDER "${ideFolderSource}")

# Setup project settings
set_project_warnings(${targetName})  # Which warnings to enable
set_compile_options(${targetName})   # Which extra compiler flags to enable
set_output_directory(${targetName})  # Set the output directory of the library

# Copy header files to output after build
copy_headers_to_output("${targetName}" "${headers}" "")

# Specify version
target_compile_definitions(${targetName} PUBLIC VERSION_MAJOR=0)
target_compile_definitions(${targetName} PUBLIC VERSION_MINOR=0)
target_compile_definitions(${targetName} PUBLIC VERSION_PATCH=1)

# System installation
# install(TARGETS ${targetName} DESTINATION lib)
# install(FILES ${headers} DESTINATION include/Logger)