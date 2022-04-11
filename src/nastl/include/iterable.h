#ifndef PPP_SRC_NASTL_INCLUDE_ITERABLE_H
#define PPP_SRC_NASTL_INCLUDE_ITERABLE_H

#include <ky/nastl/any.h>

#include <memory>

namespace ky::nastl {

class iterator {
public:
  class impl;
  iterator(std::unique_ptr<impl>);  // NOLINT(google-explicit-constructor)
  virtual ~iterator();

  friend bool operator==(const iterator &x, const iterator &y);
  friend iterator &operator++(iterator &x);

  any &operator->() const;
  any &operator*() const;

private:
  std::unique_ptr<impl> impl_;
};

class iterable {
public:
  [[nodiscard]] virtual iterator begin() const = 0;
  [[nodiscard]] virtual iterator end() const = 0;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_ITERABLE_H
