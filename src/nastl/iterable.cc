#include <ky/nastl/iterable.h>

#include "iterator_impl.h"

namespace ky::nastl {

iterator::iterator(std::unique_ptr<impl> impl) : impl_(std::move(impl)) {}

iterator::iterator(const iterator &other) : impl_(other.impl_->add(0)) {}

iterator::~iterator() = default;

bool operator==(const iterator &x, const iterator &y) {
  return x.impl_->equals(*y.impl_);
}

iterator &operator++(iterator &x) {
  x.impl_->increment();
  return x;
}

iterator operator+(const iterator &x, integer delta) {
  return {x.impl_->add(delta)};
}

any &iterator::operator->() const { return impl_->dereference(); }

any &iterator::operator*() const { return impl_->dereference(); }

}  // namespace ky::nastl