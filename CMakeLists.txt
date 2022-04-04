cmake_minimum_required(VERSION 3.22)
project(ppp VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)

set(KYDEPS_BOILERPLATE_CLANG_TIDY OFF)
set(KYDEPS_TARGETS glog GTest)

include(FetchContent)
FetchContent_Declare(
    kydeps_boilerplate
    GIT_REPOSITORY https://github.com/kydeps/boilerplate.git
    GIT_TAG feature/kydeps)
FetchContent_MakeAvailable(kydeps_boilerplate)
KyDepsAddBoilerplate()

find_package(GTest)
find_package(glog)

add_subdirectory(src)
