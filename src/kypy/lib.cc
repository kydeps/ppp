#include <ky/py/lib.h>
#include <ky/py/string.h>

#include <iostream>

#include "impl.h"

namespace kypy {

namespace {

std::string str_any_(const any& v);

std::string str_(const list& v) {
  std::string result = "[";
  bool first = true;
  for (auto& vv : v) {
    if (first) {
      first = false;
    } else {
      result += ", ";
    }
    result += str_any_(vv);
  }
  return result + "]";
}

std::string str_(const string& v) {
  std::string result;
  for (auto& vv : v) {
    result.push_back(
        static_cast<char>(std::get<integer>(impl::impl_::get(vv))));
  }
  return result;
}

class str_dispatch {
public:
  std::string operator()(std::monostate) { return ""; }
  std::string operator()(integer v) { return std::to_string(v); }
  std::string operator()(character v) { throw NotImplemented(); }
  std::string operator()(const list& v) { return str_(v); }
  std::string operator()(const string& v) { return str_(v); }
};

std::string str_any_(const any& v) {
  return std::visit(str_dispatch(), impl::impl_::get(v));
}

}  // namespace

void print(const any& x) { std::cout << str_any_(x) << std::endl; }

any str(const any& x) { return str_any_(x).c_str(); }

std::ostream& operator<<(std::ostream& s, const any& x) {
  return s << str_any_(x);
}

}  // namespace kypy