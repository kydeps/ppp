#include <ppp/ppp.h>

#include "visitor.h"

namespace ppp {

class EqualityVisitor final : public Visitor {
public:
  EqualityVisitor(const var &y) : y_(y) {}

  bool GetResult() const { return result_; }

protected:
  void visit(int x) override { result_ = (x == std::any_cast<int>(y_.value_)); }

  void visit(list_<var> x) override {
    auto y = std::any_cast<list_<var>>(y_.value_);
    result_ = len(x) == len(y) && std::equal(x.begin(), x.end(), y.begin());
  }

private:
  bool result_;
  const var &y_;
};

bool operator==(const var &x, const var &y) {
  auto v = EqualityVisitor(y);
  try {
    v.dispatch(x);
  } catch (std::bad_any_cast) {
    throw ValueError();
  }
  return v.GetResult();
}

class LessThanVisitor final : public Visitor {
public:
  LessThanVisitor(const var &y) : y_(y) {}

  bool GetResult() const { return result_; }

protected:
  void visit(int x) override { result_ = (x < std::any_cast<int>(y_.value_)); }

  void visit(list_<var> x) override {
    auto y = std::any_cast<list_<var>>(y_.value_);
    result_ = std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
  }

private:
  bool result_;
  const var &y_;
};

bool operator<(const var &x, const var &y) {
  auto v = LessThanVisitor(y);
  try {
    v.dispatch(x);
  } catch (std::bad_any_cast) {
    throw ValueError();
  }
  return v.GetResult();
}

}  // namespace ppp