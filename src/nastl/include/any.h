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

class any final : public sequence {
public:
  any();

  any(int v);      // NOLINT(google-explicit-constructor)
  any(integer v);  // NOLINT(google-explicit-constructor)

  any(const object &v);  // NOLINT(google-explicit-constructor)

  any(const any &v);

  any(const char *);         // NOLINT(google-explicit-constructor)
  any(const std::string &);  // NOLINT(google-explicit-constructor)

  void accept(visitor &v) const;

  friend bool operator==(const any &x, const any &y);
  friend bool operator<(const any &x, const any &y);
  friend any operator+(const any &x, const any &y);

  friend std::ostream &operator<<(std::ostream &s, const any &x);

  template <typename T>
  std::shared_ptr<T> get_object() const {
    auto v = std::get<std::shared_ptr<object>>(value_);
    return std::dynamic_pointer_cast<T>(v);
  }

  template <typename T>
  [[nodiscard]] integer get() const {
    return std::get<T>(value_);
  }

  // sequence and iterable

  [[nodiscard]] iterator begin() const override;
  [[nodiscard]] iterator end() const override;
  [[nodiscard]] integer size() const override;

  any &operator[](const integer &) override;

  std::shared_ptr<object> operator ->() {
    return get_object<object>();
  }

//  object &operator *() {
//    return get_object<object>();
//  }

protected:
  void replace(integer bIndex, integer eIndex, const sequence &) override;

private:
  using type = std::variant<std::monostate, integer, std::shared_ptr<object>>;

  type value_;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_ANY_H
