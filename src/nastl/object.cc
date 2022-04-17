#include <ky/nastl/exception.h>
#include <ky/nastl/object.h>

#include <iostream>
#include <limits>

namespace ky::nastl {

#define NOT_IMPLEMENTED()                                             \
  throw std::runtime_error(                                           \
      std::string() + typeid(*this).name() + " does not implement " + \
      __PRETTY_FUNCTION__)

object::~object() = default;

iterator object::begin() const { NOT_IMPLEMENTED(); }
iterator object::end() const { NOT_IMPLEMENTED(); }
integer object::size() const { NOT_IMPLEMENTED(); }
any &object::operator[](const integer &) const { NOT_IMPLEMENTED(); }
any object::split(const any &, const any &) const { NOT_IMPLEMENTED(); }
any object::strip(const any &chars) const { NOT_IMPLEMENTED(); }
void object::append(const any &) { NOT_IMPLEMENTED(); }
void object::extend(const any &) { NOT_IMPLEMENTED(); }
void object::insert(const any &, const any &) { NOT_IMPLEMENTED(); }
void object::clear() { NOT_IMPLEMENTED(); }
any object::copy() const { NOT_IMPLEMENTED(); }
void object::reverse() { NOT_IMPLEMENTED(); }
any object::count(const any &) const { NOT_IMPLEMENTED(); }
any object::index(const any &, const any &, const any &) const {
  NOT_IMPLEMENTED();
}
void object::remove(const any &) { NOT_IMPLEMENTED(); }
any object::pop(const any &) { NOT_IMPLEMENTED(); }
void object::sort(const std::function<any(any)> &, bool) { NOT_IMPLEMENTED(); }
void object::replace(integer, integer, const sequence &) { NOT_IMPLEMENTED(); }
bool object::equals(const object &) const { NOT_IMPLEMENTED(); }
bool object::less(const object &) const { NOT_IMPLEMENTED(); }
std::unique_ptr<object> object::clone() const { NOT_IMPLEMENTED(); }

any object::split(const any &index) const {
  return split(index, std::numeric_limits<integer>::max());
}

any object::strip() const { return strip("\n\t "); }

any object::index(const any &value, const any &bIndex) const {
  return index(value, bIndex, size());
}

any object::index(const any &value) const { return index(value, 0); }

any object::pop() { return pop(-1); }

void object::sort(const std::function<any(any)> &key) { sort(key, false); }

void object::sort(bool reverse) {
  sort([](auto key) { return key; }, reverse);
}

void object::sort() {
  sort([](auto key) { return key; });
}

}  // namespace ky::nastl