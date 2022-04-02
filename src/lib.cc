#include "lib.h"

#include <iostream>

class Visitor {
public:
  void dispatch(var x) {
    if (x.type() == typeid(int)) {
      visit(std::any_cast<int>(x));
    } else if (x.type() == typeid(List)) {
      visit(std::any_cast<List>(x));
    } else {
      std::cerr << "cannot handle type " << x.type().name() << std::endl;
      abort();
    }
  }

protected:
  virtual void visit(int x) = 0;
  virtual void visit(List x) = 0;
};

struct List::Impl {
  Impl(std::initializer_list<var> l) : values_(l) {}

  std::vector<var> values_;
};

List::List(std::initializer_list<var> l)
    : impl_(std::make_shared<List::Impl>(l)) {}

void List::append(var x) { impl_->values_.push_back(x); }

List::iterator List::begin() { return impl_->values_.begin(); }

List::iterator List::end() { return impl_->values_.end(); }

List list() { return list({}); }

List list(std::initializer_list<var> l) { return List(l); }

class ToStringVisitor final : public Visitor {
public:
  const std::string &GetResult() const { return result_; }

protected:
  void visit(int x) override { result_ = std::to_string(x); }

  void visit(List x) override {
    std::string result = "[";
    bool first = true;
    for (auto &value : x.impl_->values_) {
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

void print(var x) {
  auto v = ToStringVisitor();
  v.dispatch(x);
  std::cout << v.GetResult() << std::endl;
}
