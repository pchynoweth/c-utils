project(heap_tests)

file(GLOB SOURCES *.c)
make_check_test(${PROJECT_NAME}
    SOURCES ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} heap)
