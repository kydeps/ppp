#include <ky/py/any.h>
#include <ky/py/exception.h>
#include <ky/py/len.h>
#include <ky/py/list.h>

#include "impl.h"

namespace kypy {

list::list() : impl_(std::make_shared<impl::list_>()) {}

list::list(std::initializer_list<any> values)
    : impl_(std::make_shared<impl::list_>(values)) {}

list::list(const list_slice &slice)
    : impl_(std::make_shared<impl::list_>(
          slice.l_.begin() + slice.from_index_,
          slice.l_.begin() + slice.to_index_)) {}

void list::append(const any &x) { insert(size(), x); }

void list::extend(any x) { slice(size()) = std::move(x); }

void list::insert(const any &i, const any &x) { slice(i, i) = list({x}); }

any list::index(const any &x, const any &from_index, const any &to_index) {
  auto &v = impl_->values_;
  auto b = v.begin() + check_index(from_index, true);
  auto e = v.begin() + check_index(to_index, true);
  auto it = std::find(b, e, x);
  if (it == e) {
    throw ValueError();
  }
  return it - v.begin();
}

any list::index(const any &x, const any &from_index) {
  return index(x, from_index, size());
}

any list::index(const any &x) { return index(x, 0); }

void list::remove(const any &x) {
  auto i = index(x);
  pop(i);
}

any list::pop(const any &i) {
  auto result = this->operator[](i);
  auto index = check_index(i, false);
  slice(index, index + 1) = list();
  return result;
}

any list::pop() { return pop(-1); }

void list::clear() { slice(0) = list(); }

any list::count(const any &x) {
  return std::count(impl_->values_.begin(), impl_->values_.end(), x);
}

list list::copy() { return list(slice(0)); }

void list::reverse() {
  std::reverse(impl_->values_.begin(), impl_->values_.end());
}

void list::sort(const std::function<any(any)> &key, bool reverse) {
  auto compare = [key, reverse](const any &x, const any &y) {
    return (key(x) < key(y)) != reverse;
  };
  std::sort(impl_->values_.begin(), impl_->values_.end(), compare);
}

void list::sort(const std::function<any(any)> &key) { sort(key, false); }

void list::sort(bool reverse) {
  sort([](auto x) { return x; }, reverse);
}

void list::sort() { sort(false); }

any list::operator[](const any &i) {
  auto index = check_index(i, false);
  return impl_->values_[index];
}

bool operator==(const list &x, const list &y) {
  return x.impl_->values_ == y.impl_->values_;
}

list_slice list::slice(const any &from_index, const any &to_index) {
  auto from_i = check_index(from_index, true);
  auto to_i = check_index(to_index, true);
  return {from_i, to_i, *this};
}

list_slice list::slice(const any &from_index) {
  return {check_index(from_index, true), *this};
}

any *list::begin() const { return &impl_->values_[0]; }

any *list::end() const { return begin() + impl_->values_.size(); }

integer list::size() { return static_cast<integer>(impl_->values_.size()); }

integer list::check_index(const any &i, bool allow_end) {
  auto index = std::get<integer>(impl::impl_::get(i));
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

void list::replace(integer from_index, integer to_index, const any &l) {
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

list_slice::list_slice(integer from_index, integer to_index, list &l)
    : from_index_(from_index),
      to_index_(to_index),
      l_(l) {}

list_slice::list_slice(integer from_index, list &l)
    : from_index_(from_index),
      to_index_(l.size()),
      l_(l) {}

void list_slice::operator=(any &&v) { l_.replace(from_index_, to_index_, v); }

}  // namespace kypy