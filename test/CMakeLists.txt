# Create the Test executable (test) linking the libraries common & aos
add_executable(testaos testaos.cpp)
target_link_libraries (testaos aos common GTest::gtest_main)
gtest_discover_tests(testaos)

# Create the Test executable (test) linking the libraries common & soa
add_executable(testsoa testsoa.cpp)
target_link_libraries(testsoa soa common GTest::gtest_main)
gtest_discover_tests(testsoa)