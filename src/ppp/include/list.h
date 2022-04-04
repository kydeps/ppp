#pragma once

#include <vector>

#include "ppp_base.h"
#include "var.h"

namespace ppp {

template <typename T>
class list_slice_;

template <typename T>
class list_ {
public:
  // API -----------------------------------------------------------------------

  list_() : values_(std::make_shared<std::vector<T>>()) {}

  list_(std::initializer_list<T> l)
      : values_(std::make_shared<std::vector<T>>(l)) {}

  list_(const list_slice_<T> &l)
      : values_(std::make_shared<std::vector<T>>(
            l.values_.begin() + l.from_index_,
            l.values_.begin() + l.to_index_)) {}

  void append(T x) { values_->push_back(x); }

  void extend(list_<T> x) {
    values_->insert(values_->end(), x.begin(), x.end());
  }

  void insert(int i, T x) {
    values_->insert(values_->begin() + check_index(i), x);
  }  

  T pop(int i) {
    i = check_index(i);
    auto result = (*values_)[i];
    values_->erase(values_->begin() + i);
    return result;
  }

  T pop() {
    return pop(-1);
  }

  T &operator[](int index) { return (*values_)[check_index(index)]; };

  list_slice_<T> slice(int from_index, int to_index) {
    return list_slice_(
        *values_,
        check_index(from_index),
        check_index(to_index));
  }

  list_slice_<T> slice(int from_index) {
    return list_slice_(*values_, check_index(from_index), values_->size());
  }

  // Internals -----------------------------------------------------------------

  int check_index(int i) {
    if (i < 0) {
      i = values_->size() + i;
    }
    if (i < 0 || i >= values_->size()) {
      throw IndexError();
    }
    return i;
  }

  using iterator = typename std::vector<T>::iterator;

  iterator begin() { return values_->begin(); };
  iterator end() { return values_->end(); }

  std::shared_ptr<std::vector<T>> values_;
};

using list = list_<var>;

template <typename T>
class list_slice_ {
public:
  void operator=(const list_<T> &l) {
    auto &src = *l.values_;
    auto src_from = src.begin();
    auto src_to = src.end();

    auto &dst = values_;
    auto dst_from = dst.begin() + from_index_;
    auto dst_to = dst.begin() + to_index_;

    size_t src_len = src.size();
    size_t dst_len = dst_to - dst_from;

    if (dst_len < src_len) {
      std::copy(src_from, src_from + dst_len, dst_from);
      dst.insert(dst_to, src_from + dst_len, src_to);
    } else {  // dst_len >= src_len
      std::copy(src_from, src_to, dst_from);
      dst.erase(dst_from + src_len, dst_to);
    }
  }

private:
  friend class list_<T>;

  list_slice_(std::vector<T> &values, int from_index, int to_index)
      : values_(values),
        from_index_(from_index),
        to_index_(to_index) {}

  list_slice_(const list_slice_ &) = delete;

  int from_index_;
  int to_index_;
  std::vector<T> &values_;
};

}  // namespace ppp
