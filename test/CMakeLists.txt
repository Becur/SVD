project(tests)

set(test_matrix_source test_matrix.cpp test_matrix.h assert.h)
add_executable(test_matrix ${test_matrix_source})
target_link_libraries(test_matrix gtest gtest_main)

add_test(NAME TestMatrix COMMAND test_matrix)

set(test_SVD_source test_SVD.cpp test_SVD.h assert.h)
add_executable(test_SVD ${test_SVD_source})
target_link_libraries(test_SVD gtest gtest_main)

add_test(NAME TestSVD COMMAND test_SVD)