#pragma once

#include <ppp/list.h>
#include <ppp/ppp_base.h>

#include <string>

namespace ppp {

std::string str(var x);

inline std::string str(int x) {
  return std::to_string(x);
}

template <typename T>
inline std::string str(list_<T> x) {
  std::string result = "[";
  bool first = true;
  for (auto &value : *x.values_) {
    if (first) {
      first = false;
    } else {
      result += ", ";
    }
    result += str(value);
  }
  return result + "]";
}

}  // namespace ppp