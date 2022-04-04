#pragma once

#include <any>

namespace ppp {

class var {
public:
  template <typename T>
  var(const T &value) : value_(value) {}

  std::any value_;
};

}  // namespace ppp
