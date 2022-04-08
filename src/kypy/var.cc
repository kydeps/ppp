#include <ky/py/exception.h>
#include <ky/py/list.h>
#include <ky/py/var.h>

#include "impl.h"

namespace kypy {

var::var() : impl_(std::make_shared<impl::var_>()) {}

var::var(int x) : impl_(std::make_shared<impl::var_>(x)) {}

var::var(const char *x) : impl_(std::make_shared<impl::var_>(x)) {}

var::var(const list &x) : impl_(std::make_shared<impl::var_>(x)) {}

var::~var() = default;

// impl::var_ &var::get() { return *impl_; }

const var None = var();

bool operator==(const var &x, const var &y) {
  return x.impl_->value_ == y.impl_->value_;
}

var *var::begin() const {
  return std::visit(
      impl::overloaded{
          [](list v) -> var * { return v.begin(); },
          [](auto) -> var * { throw TypeError(); },
      },
      impl_->value_);
}

var *var::end() const {
  return std::visit(
      impl::overloaded{
          [](list v) -> var * { return v.end(); },
          [](auto) -> var * { throw TypeError(); },
      },
      impl_->value_);
}

}  // namespace kypy