function(make_check_test NAME)
    cmake_parse_arguments(MAKE_TEST
        "" # options
        "" # single value keywords
        "SOURCES;LIBS" # multi-value keywords
        ${ARGN}
    )

    find_package(Check REQUIRED)
    include_directories(${CHECK_INCLUDE_DIRS})
    #link_directories(${CHECK_LIBRARY_DIRS})

    add_executable(${NAME} ${MAKE_TEST_SOURCES})
    target_link_libraries(${NAME} ${CHECK_LIBRARIES})

    add_test(NAME ${NAME} COMMAND ${NAME})
endfunction()