#ifndef PPP_SRC_KYPY_INCLUDE_LIST_H
#define PPP_SRC_KYPY_INCLUDE_LIST_H

#include <ky/py/any.h>

#include <functional>
#include <initializer_list>

namespace kypy {

namespace impl {
class list_;
}

class list_slice final {
public:
  void operator=(any &&v);

  list_slice() = delete;
  list_slice(const list_slice &) = delete;
  list_slice(list_slice &&) = delete;

private:
  friend class list;

  list_slice(integer from_index, integer to_index, list &l);
  list_slice(integer from_index, list &l);

  list &l_;
  int from_index_;
  int to_index_;
};

class list final {
public:
  list();
  list(std::initializer_list<any> values);

  void append(const any &x);
  void extend(any x);
  void insert(const any &i, const any &x);
  void clear();
  any count(const any &x);
  list copy();
  void reverse();
  void remove(const any &x);

  any index(const any &x, const any &from_index, const any &to_index);
  any index(const any &x, const any &from_index);
  any index(const any &x);

  any pop(const any &i);
  any pop();

  void sort(const std::function<any(any)> &key, bool reverse);
  void sort(const std::function<any(any)> &key);
  void sort(bool reverse);
  void sort();

  any operator[](const any &i);
  friend bool operator==(const list &x, const list &y);

  list_slice slice(const any &from_index, const any &to_index);
  list_slice slice(const any &from_index);

  [[nodiscard]] any *begin() const;
  [[nodiscard]] any *end() const;

private:
  friend class impl::impl_;
  friend class list_slice;

  integer size();
  integer check_index(const any &i, bool allow_end);

  void replace(integer from_index, integer to_index, const any &l);

  explicit list(const list_slice &slice);

  std::shared_ptr<impl::list_> impl_;
};

}  // namespace kypy

#endif  // PPP_SRC_KYPY_INCLUDE_LIST_H
