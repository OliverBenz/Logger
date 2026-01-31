cmake_minimum_required(VERSION 3.16)

project(Logger VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LOGGER_IS_TOP_LEVEL OFF)
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(LOGGER_IS_TOP_LEVEL ON)
endif()

# Project Options
option(LOGGER_BUILD_TESTS "Build Logger unit tests" ${LOGGER_IS_TOP_LEVEL})
option(LOGGER_BUILD_EXAMPLES "Build Logger examples" ${LOGGER_IS_TOP_LEVEL})
option(LOGGER_ENABLE_INSTALL "Enable install/export targets for Logger" ${LOGGER_IS_TOP_LEVEL})

# Dependencies Options
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "Use previously downloaded FetchContent sources" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "Do not install googletest" FORCE)
set(INSTALL_GMOCK OFF CACHE BOOL "Do not install googlemock" FORCE)

# Installation
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Setup project settings
add_subdirectory(lib)

project_settings_configure_install_layout(
    LOGGER_INSTALL_ARCH
    LOGGER_INSTALL_CONFIG
    LOGGER_INSTALL_BASE
    PROJECT_NAME ${PROJECT_NAME}
    INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}
)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/src")

if(LOGGER_BUILD_TESTS)
    enable_testing()
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/tests")
endif()
if(LOGGER_BUILD_EXAMPLES)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/examples")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/LoggerConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/LoggerConfig.cmake"
    INSTALL_DESTINATION "${LOGGER_INSTALL_BASE}/${CMAKE_INSTALL_LIBDIR}/cmake/Logger"
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/LoggerConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

if(LOGGER_ENABLE_INSTALL)
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/LoggerConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/LoggerConfigVersion.cmake"
        DESTINATION "${LOGGER_INSTALL_BASE}/${CMAKE_INSTALL_LIBDIR}/cmake/Logger"
    )
 endif()
