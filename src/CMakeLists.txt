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

target_compile_features(${targetName} PUBLIC cxx_std_20)
target_include_directories(${targetName}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
        $<INSTALL_INTERFACE:${LOGGER_INSTALL_BASE}/include/Logger>
)
set_target_properties(${targetName} PROPERTIES FOLDER "${IDE_FOLDER_SOURCE}")

# Setup project settings
set_project_warnings(${targetName})  # Which warnings to enable
set_compile_options(${targetName})   # Which extra compiler flags to enable
set_output_directory(${targetName})  # Set the output directory of the library

# Copy header files to output after build
copy_headers_to_output("${targetName}" "${headers}" "Logger")

# Specify version
target_compile_definitions(${targetName} PUBLIC LOGVERSION_MAJOR=1)
target_compile_definitions(${targetName} PUBLIC LOGVERSION_MINOR=0)
target_compile_definitions(${targetName} PUBLIC LOGVERSION_PATCH=0)

# System installation
if(LOGGER_ENABLE_INSTALL)
    install(TARGETS ${targetName}
        EXPORT LoggerTargets
        ARCHIVE DESTINATION ${LOGGER_INSTALL_BASE}/lib/${LOGGER_INSTALL_ARCH}/${LOGGER_INSTALL_CONFIG}
        LIBRARY DESTINATION ${LOGGER_INSTALL_BASE}/lib/${LOGGER_INSTALL_ARCH}/${LOGGER_INSTALL_CONFIG}
        RUNTIME DESTINATION ${LOGGER_INSTALL_BASE}/bin/${LOGGER_INSTALL_ARCH}/${LOGGER_INSTALL_CONFIG}
    )
	install(
		DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/Logger
		DESTINATION ${LOGGER_INSTALL_BASE}/include
	)
    install(EXPORT LoggerTargets
        FILE LoggerTargets.cmake
        NAMESPACE Logger::
        DESTINATION ${LOGGER_INSTALL_BASE}/lib/cmake
    )
endif()
