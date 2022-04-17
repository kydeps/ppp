#ifndef PPP_SRC_NASTL_INCLUDE_ANY_H
#define PPP_SRC_NASTL_INCLUDE_ANY_H

#include <ky/nastl/exception.h>
#include <ky/nastl/object.h>
#include <ky/nastl/sequence.h>
#include <ky/nastl/types.h>

#include <functional>
#include <variant>

#define lambda(x, y) [](auto x) { return y; }

namespace ky::nastl {

class visitor;

class any final {
public:
  any();

  any(int v);      // NOLINT(google-explicit-constructor)
  any(integer v);  // NOLINT(google-explicit-constructor)

  any(const object &v);  // NOLINT(google-explicit-constructor)

  any(const any &v);

  any(const char *);         // NOLINT(google-explicit-constructor)
  any(const std::string &);  // NOLINT(google-explicit-constructor)

  any &operator[](const integer &) const;
  std::shared_ptr<object> operator->() const;

  [[nodiscard]] iterator begin() const;
  [[nodiscard]] iterator end() const;

  void accept(visitor &v) const;

  template <typename T>
  [[nodiscard]] const T &get() const {
    return std::get<T>(value_);
  }

  template <typename T = object>
  const T &as_object() const {
    return *std::dynamic_pointer_cast<T>(get<std::shared_ptr<object>>());
  }

  friend std::ostream &operator<<(std::ostream &s, const any &x);
  friend bool operator==(const any &x, const any &y);
  friend bool operator<(const any &x, const any &y);
  friend any operator+(const any &x, const any &y);

private:
  using type = std::variant<std::monostate, integer, std::shared_ptr<object>>;

  type value_;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_ANY_H
