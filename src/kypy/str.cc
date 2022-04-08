#include <ky/py/list.h>
#include <ky/py/str.h>

#include "impl.h"

namespace kypy {

namespace {

std::string str_(var v);

std::string str_(list &v) {
  std::string result = "[";
  bool first = true;
  for (auto &vv : impl::impl_::get(v)) {
    if (first) {
      first = false;
    } else {
      result += ", ";
    }
    result += str_(vv);
  }
  return result + "]";
}

class str_dispatch {
public:
  std::string operator()(std::monostate) { return ""; }
  std::string operator()(int v) { return std::to_string(v); }
  std::string operator()(std::string v) { return v; }
  std::string operator()(list v) { return str_(v); }
};

std::string str_(var v) { return std::visit(str_dispatch(), impl::impl_::get(v)); }

}  // namespace

var str(var x) { return str_(x).c_str(); }

}  // namespace kypy