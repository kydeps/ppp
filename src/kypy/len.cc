#include <ky/py/exception.h>
#include <ky/py/list.h>

#include "impl.h"

namespace kypy {

namespace {

class len_dispatch {
public:
  integer operator()(std::monostate) { throw TypeError(); }
  integer operator()(integer) { throw TypeError(); }
  integer operator()(character) { throw TypeError(); }
  integer operator()(const std::string& v) { return v.size(); }
  integer operator()(const list& v) { return v.end() - v.begin(); }
  integer operator()(const string& v) { return v.end() - v.begin(); }
};

}  // namespace

any len(const any& x) {
  return std::visit(len_dispatch(), impl::impl_::get(x));
}

}  // namespace kypy