add_executable(unit_tests tests_main.c)
target_link_libraries(unit_tests PRIVATE vector)
add_test(NAME AllTests COMMAND unit_tests)