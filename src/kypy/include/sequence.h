#ifndef PPP_SRC_KYPY_INCLUDE_SEQUENCE_H
#define PPP_SRC_KYPY_INCLUDE_SEQUENCE_H

#include <ky/py/any.h>

#include <initializer_list>
#include <memory>

namespace kypy {

namespace impl {
class sequence_;
}

class sequence;

class slice {
public:
  void operator=(sequence &&v);

  slice() = delete;
  slice(const slice &) = delete;
  slice(slice &&) = delete;

private:
  friend class sequence;

  slice(integer bi, integer ei, sequence &s);

  sequence &s_;
  integer bi_;
  integer ei_;
};

class sequence {
public:
  sequence();
  sequence(std::initializer_list<any> values);

  any operator[](const any &i) const;

  friend bool operator==(const sequence &x, const sequence &y);
  friend bool operator<(const sequence &x, const sequence &y);

  [[nodiscard]] any *begin() const;
  [[nodiscard]] any *end() const;

private:
  friend class slice;
  void replace(integer bi, integer ei, const sequence &s);

  std::shared_ptr<impl::sequence_> impl_;
};

}  // namespace kypy

#endif  // PPP_SRC_KYPY_INCLUDE_SEQUENCE_H
