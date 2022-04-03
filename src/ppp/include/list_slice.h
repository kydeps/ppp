#pragma once

#include "ppp_base.h"

namespace ppp {

template <typename T>
class list_;

template <typename T = var>
class list_slice_ {
public:
  // FIXME: this should accept `iterable` instead...
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

  operator list_<T>() {
    return list_(*this);
  }

private:
  friend class list_<T>;

  list_slice_(std::vector<T> &values, int from_index, int to_index)
      : values_(values),
        from_index_(from_index),
        to_index_(to_index) {}

  list_slice_(const list_slice_ &) = delete;
  list_slice_(list_slice_ &&) = delete;

  int from_index_;
  int to_index_;
  std::vector<T> &values_;
};

}  // namespace ppp

// template <typename T>
// ppp::list<T> operator ppp::list<T>(const ppp::list_slice<T> &l) {
//   return ppp::list<T>(l);
// }