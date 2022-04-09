#include <ky/py/any.h>
#include <ky/py/exception.h>
#include <ky/py/list.h>

#include "impl.h"

namespace kypy {

any::any() : impl_(std::make_shared<impl::any_>()) {}

any::any(int x) : impl_(std::make_shared<impl::any_>(x)) {}

any::any(integer x) : impl_(std::make_shared<impl::any_>(x)) {}

any::any(const char *x) : impl_(std::make_shared<impl::any_>(x)) {}

any::any(const list &x) : impl_(std::make_shared<impl::any_>(x)) {}

any::~any() = default;

// impl::any_ &any::get() { return *impl_; }

const any None = any();

bool operator==(const any &x, const any &y) {
  return x.impl_->value_ == y.impl_->value_;
}

bool operator<(const any &x, const any &y) {
  return x.impl_->value_ < y.impl_->value_;
}

any operator+(const any &x, const any &y) {
  return std::visit(
      impl::overloaded{
          [&y](integer v) -> any {
            return v + std::get<integer>(y.impl_->value_);
          },
          [](list v) -> any { throw NotImplemented(); },
          [](auto) -> any { throw TypeError(); }},
      x.impl_->value_);
}

any *any::begin() const {
  return std::visit(
      impl::overloaded{
          [](list v) -> any * { return v.begin(); },
          [](auto) -> any * { throw TypeError(); },
      },
      impl_->value_);
}

any *any::end() const {
  return std::visit(
      impl::overloaded{
          [](list v) -> any * { return v.end(); },
          [](auto) -> any * { throw TypeError(); },
      },
      impl_->value_);
}

}  // namespace kypy