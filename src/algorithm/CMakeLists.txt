project(algorithm)

file(GLOB SOURCES *.c)
add_library(${PROJECT_NAME}
    STATIC
    ${SOURCES}
)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)