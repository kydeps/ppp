#ifndef PPP_SRC_KYPY_LIST_IMPL_H
#define PPP_SRC_KYPY_LIST_IMPL_H

#include <ky/py/var.h>

#include <initializer_list>
#include <vector>

namespace kypy::impl {

class list_ {
public:
  using values_t = std::vector<var>;

  list_() = default;
  list_(std::initializer_list<var> values) : values_(values) {}

  values_t values_;
};

}  // namespace kypy::impl

#endif  // PPP_SRC_KYPY_LIST_IMPL_H
