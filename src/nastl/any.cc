#include <ky/nastl/any.h>
#include <ky/nastl/list.h>
#include <ky/nastl/string.h>

#include "string_impl.h"
#include "visitor.h"

namespace ky::nastl {

any::any() : value_() {}

any::any(int v) : value_(v) {}

any::any(integer v) : value_(v) {}

any::any(const object &v) : value_(v.clone()) {}

any::any(const any &v) = default;

any::any(const char *v) : any(string(v)){};

any::any(const std::string &v) : any(string(v.c_str())){};

void any::accept(visitor &v) const {
  struct V {
    explicit V(visitor &v) : v_(v) {}

    void operator()(std::monostate) { v_.visit(); }
    void operator()(integer x) { v_.visit(x); }
    void operator()(const std::shared_ptr<object> &x) { x->accept(v_); }

  private:
    visitor &v_;
  };

  std::visit(V(v), value_);
}

bool operator==(const any &x, const any &y) {
  struct V {
    explicit V(const any &y) : y_(y) {}

    bool operator()(std::monostate) { return any::type() == y_.value_; }
    bool operator()(integer x) { return any::type(x) == y_.value_; }
    bool operator()(const std::shared_ptr<object> &x) {
      return x->equals(*y_.get_object<object>());
    }

  private:
    const any &y_;
  };

  return std::visit(V(y), x.value_);
}

bool operator<(const any &x, const any &y) { throw not_implemented("<"); }

any operator+(const any &x, const any &y) {
  class V : public visitor {
  public:
    explicit V(const any &y) : y_(y) {}

    void visit() override { throw not_implemented("None + ..."); }

    void visit(integer x) override { result_ = x + y_.get<integer>(); }

    void visit(const list &x) override {
      auto result = list();
      result.extend(x);
      result.extend(y_);
      result_ = result;
    }

    void visit(const string &x) override {
      result_ = impl::get_value(x) + impl::get_value(y_);
    }

    const any &y_;
    any result_;
  };

  V v(y);
  x.accept(v);
  return v.result_;
}

std::ostream &operator<<(std::ostream &s, const any &x) {
  return s << string(x);
}

}  // namespace ky::nastl