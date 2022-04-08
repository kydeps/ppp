#include <ky/py/exception.h>
#include <ky/py/list.h>

#include "impl.h"

namespace kypy {

namespace {

class len_dispatch {
public:
  int operator()(std::monostate) { throw TypeError(); }
  int operator()(int) { throw TypeError(); }
  int operator()(std::string v) { return v.size(); }
  int operator()(list v) { return impl::impl_::get(v).size(); }
};

}  // namespace

var len(var x) { return std::visit(len_dispatch(), impl::impl_::get(x)); }

}  // namespace kypy