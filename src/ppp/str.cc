#include <ppp/ppp.h>

#include "visitor.h"

namespace ppp {

class ToStringVisitor final : public Visitor {
public:
  const std::string &GetResult() const { return result_; }

protected:
  void visit(int x) override { result_ = std::to_string(x); }
  void visit(list_<var> x) override { result_ = str(x); }

private:
  std::string result_;
};

std::string str(var x) {
  auto v = ToStringVisitor();
  v.dispatch(x);
  return v.GetResult();
}

}