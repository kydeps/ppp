#include <ky/nastl/sequence.h>

namespace ky::nastl {

// NOLINTNEXTLINE(misc-unconventional-assign-operator)
void slice_::operator=(const sequence &values) {
  values_.replace(bIndex_, eIndex_, values);
}

slice_::slice_(sequence &values, integer bIndex, integer eIndex)
    : values_(values),
      bIndex_(bIndex),
      eIndex_(eIndex) {}

slice_ sequence::slice(const any &bIndex, const any &eIndex) {
  return {*this, check_index(bIndex, true), check_index(eIndex, true)};
}

slice_ sequence::slice(const any &bIndex) {
  return slice(check_index(bIndex, true), size());
}

integer sequence::check_index(const any &index, bool allow_end) const {
  auto ii = index.get<integer>();
  if (ii < 0) {
    ii += size();
  }
  if (allow_end && ii == size()) {
    return ii;
  }
  if (ii < 0 || ii >= size()) {
    throw index_error();
  }
  return ii;
}

}  // namespace ky::nastl