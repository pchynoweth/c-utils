project(c-utils LANGUAGES C)

cmake_minimum_required(VERSION 3.24)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

###############################################################################
# Set build features
set(CMAKE_BUILD_TYPE Debug)

###############################################################################
include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

include(cmake/CheckTest.cmake)
include(cmake/CodeCoverage.cmake)

option(ENABLE_CODE_COVERAGE "enable code coverage" False)

if (ENABLE_CODE_COVERAGE)
  message(STATUS "Code coverage enabled")
  append_coverage_compiler_flags()

  add_custom_command(
    OUTPUT index.html
    COMMAND gcovr -r ../ --html-details index.html
  )

  add_custom_target(code_coverage
    DEPENDS index.html
    COMMAND python3 -m http.server
  )
endif()

enable_testing()

add_subdirectory(src)
