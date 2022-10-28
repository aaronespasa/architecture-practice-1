add_executable(arith_test arith_test.cpp)

target_link_libraries(arith_test arith GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(arith_test)
