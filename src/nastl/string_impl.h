#ifndef PPP_SRC_NASTL_STRING_IMPL_H
#define PPP_SRC_NASTL_STRING_IMPL_H

#include <ky/nastl/string.h>

namespace ky::nastl {

class impl {
public:
  static const std::string &get_value(const string &v) { return *v.value_; }
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_STRING_IMPL_H
