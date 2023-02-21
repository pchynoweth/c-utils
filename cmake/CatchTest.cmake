Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

function(make_catch_test NAME)
    cmake_parse_arguments(MAKE_CATCH_TEST
        "" # options
        "" # single value keywords
        "SOURCES;LIBS" # multi-value keywords
        ${ARGN}
    )

    add_executable(${NAME} ${MAKE_CATCH_TEST_SOURCES})
    target_link_libraries(${NAME} PRIVATE Catch2::Catch2WithMain)

    add_test(NAME ${NAME} COMMAND ${NAME})
endfunction()
