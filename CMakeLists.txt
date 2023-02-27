cmake_minimum_required(VERSION 3.24)

cmake_policy(SET CMP0048 NEW)

project(c-utils
  LANGUAGES C CXX
  VERSION 0.1.0
)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

###############################################################################
# Set build features
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
include(CheckCSourceCompiles)
include(CheckCSourceRuns)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckSymbolExists)
include(CheckTypeSize)

#include(cmake/CatchTest.cmake)
include(cmake/CheckTest.cmake)
include(cmake/CodeCoverage.cmake)
include(cmake/GTest.cmake)

STRING(COMPARE EQUAL Debug ${CMAKE_BUILD_TYPE} IS_DEBUG)

option(ENABLE_CODE_COVERAGE "enable code coverage" OFF)
option(ENABLE_SANITIZERS "enable sanitizers" ${IS_DEBUG})

if (ENABLE_CODE_COVERAGE)
  message(STATUS "Code coverage enabled")
  append_coverage_compiler_flags()

  add_custom_command(
    OUTPUT index.html
    COMMAND gcovr -r ${CMAKE_CURRENT_SOURCE_DIR} --html-details index.html --filter ${CMAKE_CURRENT_SOURCE_DIR}/src/
  )

  add_custom_target(code_coverage
    DEPENDS index.html
    COMMAND python3 -m http.server
  )
endif()

if (ENABLE_SANITIZERS)
  add_compile_options(-fsanitize=address -fsanitize=undefined)
  add_link_options(-fsanitize=address -fsanitize=undefined)
endif()

# options for all targets
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

enable_testing()

add_subdirectory(src)
