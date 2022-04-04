#include "visitor.h"

namespace ppp {

void Visitor::dispatch(var x) {
  if (x.value_.type() == typeid(int)) {
    visit(std::any_cast<int>(x.value_));
  } else if (x.value_.type() == typeid(list_<var>)) {
    visit(std::any_cast<list_<var>>(x.value_));
  } else {
    std::cerr << "cannot handle type " << x.value_.type().name() << std::endl;
    abort();
  }
}

}  // namespace ppp
