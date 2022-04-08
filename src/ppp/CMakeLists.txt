add_library(ppp
    visitor.cc
    str.cc
    len.cc
    eq.cc
)
target_link_libraries(ppp
    PRIVATE glog::glog
)
KyDepsPackageLibraryTarget(ppp "ppp")