#ifndef PPP_SRC_KYPY_ANY_IMPL_H
#define PPP_SRC_KYPY_ANY_IMPL_H

#include <ky/py/list.h>

#include <string>
#include <variant>

namespace kypy::impl {

class any_ {
public:
  using value_t =
      std::variant<std::monostate, intmax_t, std::string, kypy::list>;

  any_() : value_(std::monostate()) {}
  explicit any_(intmax_t x) : value_(x) {}
  explicit any_(const char *x) : value_(std::string(x)) {}
  explicit any_(list x) : value_(x) {}

  value_t value_;
};

}  // namespace kypy::impl

#endif  // PPP_SRC_KYPY_ANY_IMPL_H
