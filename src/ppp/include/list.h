#pragma once

#include <optional>
#include <vector>

#include "list_slice.h"
#include "ppp_base.h"

namespace ppp {

template <typename T = var>
class list_ {
public:
  // API -----------------------------------------------------------------------

  list_() : values_(std::make_shared<std::vector<T>>()) {}

  list_(std::initializer_list<T> l)
      : values_(std::make_shared<std::vector<T>>(l)) {}

  list_(list_slice_<T> &l)
      : values_(std::make_shared<std::vector<T>>(
            l.values_.begin() + l.from_index_,
            l.values_.begin() + l.to_index_)) {}

  void append(T x) { values_->push_back(x); }

  T &operator[](int index) { return (*values_)[index]; };

  list_slice_<T> operator()(
      std::optional<int> from_index,
      std::optional<int> to_index) {
    return list_slice_(
        *values_,
        from_index.value_or(0),
        to_index.value_or(values_->size()));
  }

  // Internals -----------------------------------------------------------------

  using iterator = typename std::vector<T>::iterator;

  iterator begin() { return values_->begin(); };
  iterator end() { return values_->end(); }

  std::shared_ptr<std::vector<T>> values_;
};

using list = list_<var>;

}  // namespace ppp
