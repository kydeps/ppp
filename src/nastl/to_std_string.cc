#include "to_std_string.h"

#include <ky/nastl/list.h>

#include "impl.h"
#include "visitor.h"

namespace ky::nastl {

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
  }

  void visit(const string &v) override {
    result_.clear();
    result_.push_back('"');
    for (const auto &c : get_value(v)) {
      if (c == '"') {
        result_ += R"(\")";
      } else {
        result_.push_back(c);
      }
    }
    result_.push_back('"');
  }
};

std::string to_std_string(const any &v) {
  ToStringVisitor visitor;
  v.accept(visitor);
  return visitor.result_;
}

}  // namespace ky::nastl
