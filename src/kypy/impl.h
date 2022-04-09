#ifndef PPP_SRC_KYPY_IMPL_H
#define PPP_SRC_KYPY_IMPL_H

#include "any_impl.h"
#include "list_impl.h"
#include "sequence_impl.h"

namespace kypy::impl {

// from https://en.cppreference.com/w/cpp/utility/variant/visit
template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

class impl_ final {
public:
  static any_::value_t get(const any &v) { return v.impl_->value_; }
//  static list_::values_t get(const list &v) { return v.impl_->values_; }
};

}  // namespace kypy::impl
#endif  // PPP_SRC_KYPY_IMPL_H
