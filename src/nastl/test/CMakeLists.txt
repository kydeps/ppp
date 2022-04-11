add_executable(nastl_test
        test1.cc
        )
target_link_libraries(nastl_test
        PRIVATE GTest::gtest GTest::gtest_main ppp::nastl
        )
kydepspackagetarget(nastl_test)

gtest_discover_tests(nastl_test)
