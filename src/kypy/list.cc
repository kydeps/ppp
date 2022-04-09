#include <ky/py/any.h>
#include <ky/py/exception.h>
#include <ky/py/len.h>
#include <ky/py/list.h>

#include "impl.h"

namespace kypy {

list::list(std::initializer_list<any> values) : sequence(values) {}

//list::list(const list_slice &slice)
//    : impl_(std::make_shared<impl::list_>(
//          slice.l_.begin() + slice.from_index_,
//          slice.l_.begin() + slice.to_index_)) {}

void list::append(const any &x) { insert(size(), x); }

void list::extend(const any &x) {
  auto l = std::get<list>(impl::impl_::get(x));
  slice(size()) = std::move(l);
}

void list::insert(const any &i, const any &x) { slice(i, i) = list({x}); }

any list::index(const any &x, const any &bi, const any &ei) {
  auto &v = impl_->values_;
  auto b = v.begin() + impl_->check_index(bi, true);
  auto e = v.begin() + impl_->check_index(ei, true);
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
  auto index = impl_->check_index(i, false);
  slice(index, index + 1) = list();
  return result;
}

any list::pop() { return pop(-1); }

void list::clear() { slice(0) = list(); }

any list::count(const any &x) {
  return std::count(impl_->values_.begin(), impl_->values_.end(), x);
}

//list list::copy() { return list(slice(0)); }

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

}  // namespace kypy