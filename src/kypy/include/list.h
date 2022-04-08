#ifndef PPP_SRC_KYPY_INCLUDE_LIST_H
#define PPP_SRC_KYPY_INCLUDE_LIST_H

#include <ky/py/var.h>

#include <initializer_list>

namespace kypy {

namespace impl {
class list_;
}

class list_slice final {
public:
  void operator =(var &&l);

private:
  friend class list;

  list_slice(int from_index, int to_index, list &l);
  list_slice(int from_index, list &l);

  list_slice() = delete;
  list_slice(const list_slice &) = delete;
  list_slice(list_slice &&) = delete;

  list &l_;
  int from_index_;
  int to_index_;
};

class list final {
public:
  list();
  list(std::initializer_list<var> values);

  void append(var x);

  friend bool operator==(const list &x, const list &y);

  list_slice slice(int from_index, int to_index);
  list_slice slice(int from_index);

  [[nodiscard]] var *begin() const;
  [[nodiscard]] var *end() const;

private:
  friend class impl::impl_;
  friend class list_slice;

  int size();
  int check_index(int index, bool allow_end);

  void replace(int from_index, int to_index, const var &l);

  std::shared_ptr<impl::list_> impl_;
};

}  // namespace kypy

#endif  // PPP_SRC_KYPY_INCLUDE_LIST_H
