#include <ppp/ppp.h>

#include <iostream>

namespace ppp {

class Visitor {
public:
  void dispatch(var x) {
    if (x.type() == typeid(int)) {
      visit(std::any_cast<int>(x));
    } else if (x.type() == typeid(list_<var>)) {
      visit(std::any_cast<list_<var>>(x));
    } else {
      std::cerr << "cannot handle type " << x.type().name() << std::endl;
      abort();
    }
  }

protected:
  virtual void visit(int x) = 0;
  virtual void visit(list_<var> x) = 0;
};

class ToStringVisitor final : public Visitor {
public:
  const std::string &GetResult() const { return result_; }

protected:
  void visit(int x) override { result_ = std::to_string(x); }

  void visit(list_<var> x) override {
    std::string result = "[";
    bool first = true;
    for (auto &value : *x.values_) {
      dispatch(value);
      if (first) {
        first = false;
      } else {
        result += ", ";
      }
      result += result_;
    }
    result += "]";
    result_ = std::move(result);
  }

private:
  std::string result_;
};

std::string str(var x) {
  auto v = ToStringVisitor();
  v.dispatch(x);
  return v.GetResult();
}

void print(var x) {
  std::cout << str(x) << std::endl;
}
}