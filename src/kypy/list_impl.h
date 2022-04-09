#ifndef PPP_SRC_KYPY_LIST_IMPL_H
#define PPP_SRC_KYPY_LIST_IMPL_H

#include <ky/py/any.h>

#include <initializer_list>
#include <vector>

namespace kypy::impl {

class list_ {
public:
  using values_t = std::vector<any>;

  list_() = default;
  list_(std::initializer_list<any> values) : values_(values) {}
  list_(any* begin, any* end) : values_(begin, end) {}

  values_t values_;
};

}  // namespace kypy::impl

#endif  // PPP_SRC_KYPY_LIST_IMPL_H
