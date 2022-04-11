file(GLOB HEADERS include/*.h)

add_library(nastl
        ${HEADERS}
        object.cc
        any.cc
        iterable.cc
        sequence.cc
        list.cc
        string.cc
        string_iter.cc
        string_from_any.cc
        )
target_link_libraries(nastl
        PRIVATE glog::glog
        )
kydepspackagelibrarytarget(nastl "ky/nastl")

add_subdirectory(test)