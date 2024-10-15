project(tests)

set(test_matrix_source test_matrix.h test_matrix.cpp assert.h main.cpp)
add_executable(test_matrix ${test_matrix_source})
target_link_libraries(test_matrix gtest gtest_main)

add_test(NAME TestMatrix COMMAND test_matrix)