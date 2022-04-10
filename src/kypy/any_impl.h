#ifndef PPP_SRC_KYPY_ANY_IMPL_H
#define PPP_SRC_KYPY_ANY_IMPL_H

#include <ky/py/list.h>
#include <ky/py/string.h>

#include <string>
#include <variant>

namespace kypy::impl {

class any_ {
public:
  using value_t = std::
      variant<std::monostate, integer, kypy::list, kypy::string>;

  any_() : value_(std::monostate()) {}
  explicit any_(integer x) : value_(x) {}
  explicit any_(const list &x) : value_(x) {}
  explicit any_(const string &x) : value_(x) {}

  value_t value_;
};

}  // namespace kypy::impl

#endif  // PPP_SRC_KYPY_ANY_IMPL_H
