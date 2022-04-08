#include <ky/py/exception.h>
#include <ky/py/len.h>
#include <ky/py/list.h>
#include <ky/py/var.h>

#include "impl.h"

namespace kypy {

list::list() : impl_(std::make_shared<impl::list_>()) {}

list::list(std::initializer_list<var> values)
    : impl_(std::make_shared<impl::list_>(values)) {}

void list::append(var x) {
  slice(size()) = list({x});
}

bool operator==(const list &x, const list &y) {
  return x.impl_->values_ == y.impl_->values_;
}

list_slice list::slice(int from_index, int to_index) {
  return {from_index, to_index, *this};
}

list_slice list::slice(int from_index) {
  return {from_index, *this};
}

var *list::begin() const { return &impl_->values_[0]; }

var *list::end() const { return begin() + impl_->values_.size(); }

int list::size() {
  return impl_->values_.size();
}

int list::check_index(int index, bool allow_end) {
  if (index < 0) {
    index += size();
  }
  if (allow_end && index == size()) {
    return index;
  }
  if (index < 0 || index >= size()) {
    throw IndexError();
  }
  return index;
}

void list::replace(int from_index, int to_index, const var &l) {
  auto &dst = impl_->values_;
  auto dst_b = dst.begin() + check_index(from_index, true);
  auto dst_e = dst.begin() + check_index(to_index, true);
  auto dst_s = dst_e - dst_b;

  auto src_b = l.begin();
  auto src_e = l.end();
  auto src_s = src_e - src_b;

  if (dst_s < src_s) {
    std::copy(src_b, src_b + dst_s, dst_b);
    dst.insert(dst_e, src_b + dst_s, src_e);
  } else {
    std::copy(src_b, src_e, dst_b);
    dst.erase(dst_b + src_s, dst_e);
  }
}

list_slice::list_slice(int from_index, int to_index, list &l)
    : from_index_(from_index),
      to_index_(to_index),
      l_(l) {}

list_slice::list_slice(int from_index, list &l)
    : from_index_(from_index),
      to_index_(l.size()),
      l_(l) {}

void list_slice::operator=(var &&l) { l_.replace(from_index_, to_index_, l); }

}  // namespace kypy