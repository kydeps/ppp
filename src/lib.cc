#include "lib.h"

#include <iostream>
#include <vector>

class Visitor {
public:
  void dispatch(var x) {
    if (x.type() == typeid(int)) {
      visit(std::any_cast<int>(x));
    } else if (x.type() == typeid(list)) {
      visit(std::any_cast<list>(x));
    } else {
      std::cerr << "cannot handle type " << x.type().name() << std::endl;
      abort();
    }
  }

protected:
  virtual void visit(int x) = 0;
  virtual void visit(list x) = 0;
};

struct list_slice::Impl {
  Impl(list &l, int from_index, int to_index)
      : l_(l),
        from_index_(from_index),
        to_index_(to_index) {}

  std::vector<var> get_vector() {
    return std::vector<var>(l_.begin() + from_index_, l_.begin() + to_index_);
  }

  list &l_;
  int from_index_;
  int to_index_;
};

list_slice::list_slice(list &l, int from_index, int to_index)
    : impl_(std::make_unique<list_slice::Impl>(l, from_index, to_index)) {}

list_slice::~list_slice() = default;

list_slice::operator var() { return list(*this); }

struct list::Impl {
  Impl() {}

  Impl(std::initializer_list<var> l) : values_(l) {}
  Impl(std::vector<var> values) : values_(std::move(values)) {}

  std::vector<var> values_;
};

list::list() : impl_(std::make_shared<list::Impl>()) {}

list::list(std::initializer_list<var> l)
    : impl_(std::make_shared<list::Impl>(l)) {}

list::list(list_slice &l)
    : impl_(std::make_shared<list::Impl>(l.impl_->get_vector())) {}

void list::append(var x) { impl_->values_.push_back(x); }

// FIXME: negative indices?
var &list::operator[](int index) { return impl_->values_[index]; }

list_slice list::operator()(
    std::optional<int> from_index,
    std::optional<int> to_index) {
  return list_slice(*this, from_index.value_or(0), to_index.value_or(-1));
}

var *list::begin() { return &impl_->values_[0]; }

var *list::end() { return begin() + impl_->values_.size(); }

class ToStringVisitor final : public Visitor {
public:
  const std::string &GetResult() const { return result_; }

protected:
  void visit(int x) override { result_ = std::to_string(x); }

  void visit(list x) override {
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
