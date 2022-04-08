add_subdirectory(ppp)
add_subdirectory(kypy)

add_executable(test0 test.cc)
target_link_libraries(test0
    PRIVATE ppp::ppp GTest::gtest GTest::gtest_main
)
KyDepsPackageTarget(test0)

gtest_discover_tests(test0)
