#include <ky/nastl/list.h>
#include <ky/nastl/string.h>

#include "iterator_impl.h"
#include "visitor.h"

namespace ky::nastl {

string::string(const char *value)
    : value_(std::make_shared<std::string>(value)) {}

string::string(const string &) = default;

string::~string() = default;

integer string::size() const {
  // NOLINTNEXTLINE(cppcoreguidelines-narrowing-conversions)
  return value_->size();
}

any &string::operator[](const integer &index) {
  throw std::runtime_error("not implemented");
}

void string::accept(visitor &v) const { v.visit(*this); }

std::unique_ptr<object> string::clone() const {
  return std::make_unique<string>(*this);
}

bool string::equals(const object &other) const {
  const auto &o = dynamic_cast<const string &>(other);
  return *value_ == *o.value_;
}

}  // namespace ky::nastl