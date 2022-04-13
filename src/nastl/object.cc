#include <ky/nastl/exception.h>
#include <ky/nastl/object.h>

#include <iostream>

namespace ky::nastl {

object::~object() = default;

iterator object::begin() const { throw not_implemented("begin"); }

iterator object::end() const { throw not_implemented("begin"); }

any &object::operator[](const integer &) { throw not_implemented("[]"); }

integer object::size() const { throw not_implemented("size"); }

void object::replace(integer bIndex, integer eIndex, const sequence &sequence) {
  throw not_implemented("replace");
}

std::unique_ptr<object> object::clone() const {
  throw not_implemented("clone");
}

bool object::equals(const object &) const {
  throw not_implemented("equal");
}

bool object::less(const object &) const {
  throw not_implemented("less");
}

}  // namespace ky::nastl