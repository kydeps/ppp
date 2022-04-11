#ifndef PPP_SRC_NASTL_INCLUDE_ITERABLE_H
#define PPP_SRC_NASTL_INCLUDE_ITERABLE_H

#include <ky/nastl/any.h>

#include <memory>

namespace ky::nastl {

class iterator {
public:
  class impl;
  iterator(std::unique_ptr<impl>);  // NOLINT(google-explicit-constructor)
  iterator(const iterator &);
  virtual ~iterator();

  //  using value_type = any;
  //  using pointer = any *;
  //  using refrence = any &;
  //  using const_pointer = any *const;

  friend bool operator==(const iterator &x, const iterator &y);
  friend iterator &operator++(iterator &x);
  friend iterator operator+(const iterator &x, integer delta);

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

template <>
struct std::iterator_traits<ky::nastl::iterator> {
  using difference_type = ky::nastl::integer;
  using value_type = ky::nastl::any;
  using pointer = value_type *;
  using reference = value_type &;
  using iterator_category = std::input_iterator_tag;
};

#endif  // PPP_SRC_NASTL_INCLUDE_ITERABLE_H
