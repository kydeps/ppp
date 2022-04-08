#pragma once

#include <iostream>
#include <exception>

namespace ppp {

template <typename T>
void print(T x) {
    std::cout << str(x) << std::endl;
}

class PPPError: std::exception {};
class TypeError final : PPPError {};
class IndexError final : PPPError {};
class ValueError final : PPPError {};

}  // namespace ppp
