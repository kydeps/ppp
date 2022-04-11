#ifndef PPP_SRC_NASTL_INCLUDE_ANY_H
#define PPP_SRC_NASTL_INCLUDE_ANY_H

#include <ky/nastl/exception.h>
#include <ky/nastl/object.h>

#include <variant>

namespace ky::nastl {

using integer = intmax_t;

class visitor;

class any {
public:
  any();
  any(integer v);        // NOLINT(google-explicit-constructor)
  any(const object &v);  // NOLINT(google-explicit-constructor)

  any(const any &v);

  any(const char *);

  void accept(visitor &v) const;

  friend bool operator==(const any &x, const any &y);
  friend bool operator<(const any &x, const any &y);

  friend std::ostream &operator<<(std::ostream &s, const any &x);

  template <typename T>
  std::shared_ptr<T> get() const {
    auto v = std::get<std::shared_ptr<object>>(value_);
    return std::dynamic_pointer_cast<T>(v);
  }

private:
  using type = std::variant<std::monostate, integer, std::shared_ptr<object>>;
  type value_;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_ANY_H
