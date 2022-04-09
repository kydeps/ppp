add_subdirectory(kypy)

add_executable(test1 test1.cc)
target_link_libraries(test1
        PRIVATE GTest::gtest GTest::gtest_main ppp::kypy
        )
kydepspackagetarget(test1)

gtest_discover_tests(test1)

add_executable(example
        exmaple.cc)
target_link_libraries(example
        PRIVATE ppp::kypy)