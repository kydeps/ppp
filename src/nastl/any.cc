#include <ky/nastl/any.h>
#include <ky/nastl/list.h>
#include <ky/nastl/string.h>

#include "visitor.h"

namespace ky::nastl {

any::any() : value_() {}

any::any(integer v) : value_(v) {}

any::any(const object &v) : value_(v.clone()) {}

any::any(const any &v) = default;

any::any(const char *v) : any(string(v)){};

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
      return x->equals(*y_.get<object>());
    }

  private:
    const any &y_;
  };

  return std::visit(V(y), x.value_);
}

bool operator<(const any &x, const any &y) { return x.value_ < y.value_; }

std::ostream &operator<<(std::ostream &s, const any &x) {
  return s << string(x);
}

}  // namespace ky::nastl