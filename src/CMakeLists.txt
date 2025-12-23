set(targetName Logger)

# Get files to build
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "*.cpp")

# Create library
add_library(${targetName} STATIC
    ${headers}
    ${sources}
)
add_library(Logger::Logger ALIAS ${targetName})

# Link to thread module.
target_link_libraries(${targetName})
target_include_directories(${targetName}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:include/Logger>
)
set_target_properties(${targetName} PROPERTIES FOLDER "${ideFolderSource}")

# Setup project settings
set_project_warnings(${targetName})  # Which warnings to enable
set_compile_options(${targetName})   # Which extra compiler flags to enable
set_output_directory(${targetName})  # Set the output directory of the library

# Copy header files to output after build
copy_headers_to_output("${targetName}" "${headers}" "")

# Specify version
target_compile_definitions(${targetName} PUBLIC LOGVERSION_MAJOR=1)
target_compile_definitions(${targetName} PUBLIC LOGVERSION_MINOR=0)
target_compile_definitions(${targetName} PUBLIC LOGVERSION_PATCH=0)

# System installation
if(LOGGER_ENABLE_INSTALL)
    install(TARGETS ${targetName}
        EXPORT LoggerTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Logger
    )
    install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Logger)
    install(EXPORT LoggerTargets
        FILE LoggerTargets.cmake
        NAMESPACE Logger::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Logger
    )
endif()
