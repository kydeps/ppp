#ifndef PPP_SRC_KYPY_INCLUDE_ANY_H
#define PPP_SRC_KYPY_INCLUDE_ANY_H

#include <memory>

#define lambda(x, y) [](auto x) { return y; }

namespace kypy {

namespace impl {
class any_;
class impl_;
}  // namespace impl

class list;

using integer = intmax_t;

class any final {
public:
  any();
  any(int x);
  any(integer x);
  any(const char *x);
  any(const list &x);
  ~any();

  friend bool operator==(const any &x, const any &y);
  friend bool operator<(const any &x, const any &y);
  friend any operator+(const any &x, const any &y);

  [[nodiscard]] any *begin() const;
  [[nodiscard]] any *end() const;

private:
  friend class impl::impl_;

  std::shared_ptr<impl::any_> impl_;
};

extern const any None;

}  // namespace kypy

#endif  // PPP_SRC_KYPY_INCLUDE_ANY_H
