project(algorithm_tests)

file(GLOB SOURCES *.cxx)
make_gtest_test(${PROJECT_NAME}
    SOURCES ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} algorithm)
