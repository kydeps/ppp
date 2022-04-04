#pragma once

#include <ppp/ppp.h>

namespace ppp {

class Visitor {
public:
  void dispatch(var x);

protected:
  virtual void visit(int x) = 0;
  virtual void visit(list_<var> x) = 0;
};

}  // namespace ppp
