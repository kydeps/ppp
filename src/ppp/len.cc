#include <ppp/ppp.h>

#include "visitor.h"

namespace ppp {

class LenVisitor final : public Visitor {
public:
  int GetResult() const { return result_; }

protected:
  void visit(int x) override { throw TypeError(); }
  void visit(list_<var> x) override { result_ = x.values_->size(); }

private:
  int result_;
};

int len(var x) {
  auto v = LenVisitor();
  v.dispatch(x);
  return v.GetResult();
}

}
