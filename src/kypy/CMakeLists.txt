add_library(kypy
        include/exception.h
        include/any.h
        any.cc
        include/str.h
        str.cc
        include/list.h
        list.cc
        include/len.h
        len.cc
        )
target_link_libraries(kypy
        PRIVATE glog::glog
        )
kydepspackagelibrarytarget(kypy "ky/py")

add_executable(test1 test1.cc)
target_link_libraries(test1
        PRIVATE GTest::gtest GTest::gtest_main ppp::kypy
        )
kydepspackagetarget(test1)

gtest_discover_tests(test1)
