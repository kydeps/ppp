#include "include/sequence.h"

#include <ky/py/sequence.h>

#include "sequence_impl.h"

namespace kypy {

void slice::operator=(sequence&& v) {
  s_.replace(bi_, ei_, v);
}

slice::slice(integer bi, integer ei, sequence& s) : bi_(bi), ei_(ei), s_(s){}

sequence::sequence() : impl_(std::make_shared<impl::sequence_>()) {}

sequence::sequence(std::initializer_list<any> values)
    : impl_(std::make_shared<impl::sequence_>(values)) {}

any sequence::operator[](const any& i) const {
  return impl_->values_[impl_->check_index(i, false)];
}

bool operator==(const sequence& x, const sequence& y) {
  return x.impl_->values_ == y.impl_->values_;
}

bool operator<(const sequence& x, const sequence& y) {
  auto& x1 = x.impl_->values_;
  auto& y1 = y.impl_->values_;
  return std::lexicographical_compare(
      x1.begin(),
      x1.end(),
      y1.begin(),
      y1.end());
}

any* sequence::begin() const { return &impl_->values_[0]; }
any* sequence::end() const { return begin() + impl_->size(); }

void sequence::replace(integer bi, integer ei, const sequence& s) {
  auto& dst = impl_->values_;
  auto dst_b = dst.begin() + impl_->check_index(bi, true);
  auto dst_e = dst.begin() + impl_->check_index(ei, true);
  auto dst_s = dst_e - dst_b;

  auto src_b = s.begin();
  auto src_e = s.end();
  auto src_s = src_e - src_b;

  if (dst_s < src_s) {
    std::copy(src_b, src_b + dst_s, dst_b);
    dst.insert(dst_e, src_b + dst_s, src_e);
  } else {
    std::copy(src_b, src_e, dst_b);
    dst.erase(dst_b + src_s, dst_e);
  }
}

}  // namespace kypy
