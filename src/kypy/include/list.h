#ifndef PPP_SRC_KYPY_INCLUDE_LIST_H
#define PPP_SRC_KYPY_INCLUDE_LIST_H

#include <ky/py/any.h>
#include <ky/py/sequence.h>

#include <functional>
#include <initializer_list>

namespace kypy {

namespace impl {
class list_;
}

class list final : public sequence {
public:
  list() = default;
  list(std::initializer_list<any> values);

  void append(const any &x);
  void extend(const any &x);
  void insert(const any &i, const any &x);
  void clear();
  any count(const any &x);
  list copy();
  void reverse();
  void remove(const any &x);

  any index(const any &x, const any &bi, const any &ei);
  any index(const any &x, const any &bi);
  any index(const any &x);

  any pop(const any &i);
  any pop();

  void sort(const std::function<any(any)> &key, bool reverse);
  void sort(const std::function<any(any)> &key);
  void sort(bool reverse);
  void sort();
};

}  // namespace kypy

#endif  // PPP_SRC_KYPY_INCLUDE_LIST_H
