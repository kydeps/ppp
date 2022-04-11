#include <ky/nastl/list.h>
#include <ky/nastl/string.h>

#include "string_impl.h"
#include "visitor.h"

namespace ky::nastl {

namespace {

class ToStringVisitor final : public visitor, private impl {
public:
  std::string result_;

  void visit() override { result_ = ""; };

  void visit(integer v) override { result_ = std::to_string(v); };

  void visit(const list &v) override {
    std::string result = "[";
    bool first = true;
    for (auto &i : v) {
      if (first) {
        first = false;
      } else {
        result += ", ";
      }
      i.accept(*this);
      result += result_;
    }
    result_ = result + "]";
  };

  void visit(const string &v) override { result_ = get_value(v); };
};

std::string to_string(const any &v) {
  ToStringVisitor visitor;
  v.accept(visitor);
  return visitor.result_;
}

}  // namespace

string::string(const any &v)
    : value_(std::make_shared<std::string>(to_string(v))) {}

std::ostream &operator<<(std::ostream &s, const string &v) {
  return s << impl::get_value(v);
}

}  // namespace ky::nastl