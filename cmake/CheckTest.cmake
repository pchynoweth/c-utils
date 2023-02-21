find_package(PkgConfig REQUIRED)

# Take care about check.pc settings
pkg_check_modules( CHECK REQUIRED check )

function(make_check_test NAME)
    cmake_parse_arguments(MAKE_CHECK_TEST
        "" # options
        "" # single value keywords
        "SOURCES;LIBS" # multi-value keywords
        ${ARGN}
    )

    include_directories(${CHECK_INCLUDE_DIRS})

    add_executable(${NAME} ${MAKE_CHECK_TEST_SOURCES})
    target_link_libraries(${NAME} ${CHECK_LIBRARIES})

    add_test(NAME ${NAME} COMMAND ${NAME})
endfunction()
