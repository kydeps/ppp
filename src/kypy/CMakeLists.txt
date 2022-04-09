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
        include/lib.h
        lib.cc
        include/sequence.h
        sequence.cc
        sequence_impl.h
        sequence_impl.cc
        )
target_link_libraries(kypy
        PRIVATE glog::glog
        )
kydepspackagelibrarytarget(kypy "ky/py")
