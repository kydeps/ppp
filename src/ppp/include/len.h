#pragma once

#include <ppp/list.h>

namespace ppp {

template <typename T>
int len(list_<T> x) {
  return x.values_->size();
}

template <typename T>
int len(list_slice_<T> x) {
  return len(list_<T>(x));
}

template <typename T>
int len(T x) {
  throw TypeError();
}

}  // namespace ppp