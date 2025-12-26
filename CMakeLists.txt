cmake_minimum_required(VERSION 3.16)

project(Logger VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LOGGER_IS_TOP_LEVEL OFF)
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(LOGGER_IS_TOP_LEVEL ON)
endif()

# Normalize install prefix/old include paths for typical GNU layouts on Unix-like systems.
if(UNIX AND NOT WIN32)
    if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT OR CMAKE_INSTALL_PREFIX MATCHES "^/var/empty")
        set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Install path prefix" FORCE)
    endif()
    if(CMAKE_INSTALL_OLDINCLUDEDIR MATCHES "^/var/empty")
        set(CMAKE_INSTALL_OLDINCLUDEDIR "/usr/include" CACHE PATH "Old-style include path" FORCE)
    endif()
endif()

option(LOGGER_BUILD_TESTS "Build Logger unit tests" ${LOGGER_IS_TOP_LEVEL})
option(LOGGER_BUILD_EXAMPLES "Build Logger examples" ${LOGGER_IS_TOP_LEVEL})
option(LOGGER_ENABLE_INSTALL "Enable install/export targets for Logger" ${LOGGER_IS_TOP_LEVEL})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Setup project settings
add_subdirectory(lib)
add_subdirectory(src)

if(LOGGER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
if(LOGGER_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/LoggerConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/LoggerConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Logger
)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/LoggerConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

export(
    EXPORT LoggerTargets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/LoggerTargets.cmake
    NAMESPACE Logger::
)

if(LOGGER_ENABLE_INSTALL)
    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/LoggerConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/LoggerConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Logger
    )
endif()
