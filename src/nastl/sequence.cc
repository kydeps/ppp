#include <ky/nastl/sequence.h>

namespace ky::nastl {

slice_::slice_(sequence &values, integer bIndex, integer eIndex)
    : values_(values),
      bIndex_(bIndex),
      eIndex_(eIndex) {}

slice_ sequence::slice(const integer &bIndex, const integer &eIndex) {
  return {*this, bIndex, eIndex};
}

slice_ sequence::slice(const integer &bIndex) { return slice(bIndex, size()); }

}  // namespace ky::nastl