#include "sequence_impl.h"

#include <ky/py/exception.h>

#include "impl.h"

namespace kypy::impl {

integer sequence_::size() const { return static_cast<integer>(values_.size()); }

integer sequence_::check_index(const any& i, bool allow_end) const {
  auto ii = std::get<integer>(impl::impl_::get(i));
  if (ii < 0) {
    ii += size();
  }
  if (allow_end && ii == size()) {
    return ii;
  }
  if (ii < 0 || ii >= size()) {
    throw IndexError();
  }
  return ii;
}

}  // namespace kypy::impl