#ifndef PPP_SRC_KYPY_SEQUENCE_IMPL_H
#define PPP_SRC_KYPY_SEQUENCE_IMPL_H

#include <ky/py/any.h>

#include <initializer_list>
#include <vector>

namespace kypy::impl {

class sequence_ {
public:
  sequence_() = default;
  sequence_(std::initializer_list<any> values) : values_(values){};
  sequence_(const any *begin, const any *end) : values_(begin, end){};

  [[nodiscard]] integer size() const;
  [[nodiscard]] integer check_index(const any &i, bool allow_end) const;

  std::vector<any> values_;
};

}  // namespace kypy::impl

#endif  // PPP_SRC_KYPY_SEQUENCE_IMPL_H
