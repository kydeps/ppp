#ifndef PPP_SRC_KYPY_VAR_IMPL_H
#define PPP_SRC_KYPY_VAR_IMPL_H

#include <ky/py/list.h>

#include <string>
#include <variant>

namespace kypy::impl {

class var_ {
public:
  using value_t = std::variant<std::monostate, int, std::string, kypy::list>;

  var_() : value_(std::monostate()) {}
  explicit var_(int x) : value_(x) {}
  explicit var_(const char *x) : value_(std::string(x)) {}
  explicit var_(list x) : value_(x) {}

  value_t value_;
};

}  // namespace kypy::impl

#endif  // PPP_SRC_KYPY_VAR_IMPL_H
