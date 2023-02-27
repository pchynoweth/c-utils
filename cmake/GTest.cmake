# docs: https://github.com/google/googletest/blob/main/googletest/README.md
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

function(make_gtest_test NAME)
    cmake_parse_arguments(MAKE_GTEST_TEST
        "" # options
        "" # single value keywords
        "SOURCES;LIBS" # multi-value keywords
        ${ARGN}
    )

    include_directories(${CHECK_INCLUDE_DIRS})

    add_executable(${NAME} ${MAKE_GTEST_TEST_SOURCES})
    target_link_libraries(${NAME} GTest::gmock_main)

    add_test(NAME ${NAME} COMMAND ${NAME})
endfunction()