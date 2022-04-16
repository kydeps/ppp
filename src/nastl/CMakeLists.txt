file(GLOB HEADERS include/*.h)

add_library(nastl
        ${HEADERS}
        object.cc
        any.cc
        iterable.cc
        sequence.cc
        list.cc
        to_std_string.cc
        string.cc
        string_iter.cc
        string_from_any.cc
        string_lib.cc
        file.cc
        visitor.cc
        )
target_link_libraries(nastl
        PRIVATE glog::glog
        )
KyDepsPackageLibraryTarget(nastl "ky/nastl")

add_subdirectory(test)
add_subdirectory(examples)