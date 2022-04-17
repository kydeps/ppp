#include <ky/nastl/list.h>
#include <ky/nastl/string.h>

#include "iterator_impl.h"
#include "visitor.h"

namespace ky::nastl {

string::string() : value_(std::make_shared<std::string>()) {}

string::string(const char *value)
    : value_(std::make_shared<std::string>(value)) {}

string::string(const string &) = default;

string::~string() = default;

any string::copy() const {
  return *value_;
}

integer string::size() const {
  // NOLINTNEXTLINE(cppcoreguidelines-narrowing-conversions)
  return value_->size();
}

any &string::operator[](const integer &index) const {
  throw std::runtime_error("not implemented");
}

void string::accept(visitor &v) const { v.visit(*this); }

bool string::equals(const object &other) const {
  const auto &o = dynamic_cast<const string &>(other);
  return *value_ == *o.value_;
}

bool string::less(const object &other) const {
  const auto &o = dynamic_cast<const string &>(other);
  return *value_ < *o.value_;
}

std::unique_ptr<object> string::clone() const {
  return std::make_unique<string>(*this);
}

void string::replace(integer bIndex, integer eIndex, const sequence &s) {
  auto &dst = *value_;
  auto dst_b = dst.begin() + check_index(bIndex, true);
  auto dst_e = dst.begin() + check_index(eIndex, true);
  auto dst_s = dst_e - dst_b;

  auto &ss = dynamic_cast<const string &>(s);
  auto &src = *ss.value_;
  auto src_b = src.begin();
  auto src_e = src.end();
  auto src_s = src_e - src_b;

  if (dst_s < src_s) {
    std::copy(src_b, src_b + dst_s, dst_b);
    dst.insert(dst_e, src_b + dst_s, src_e);
  } else {
    std::copy(src_b, src_e, dst_b);
    dst.erase(dst_b + src_s, dst_e);
  }
}

}  // namespace ky::nastl