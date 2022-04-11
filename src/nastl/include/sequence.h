#ifndef PPP_SRC_NASTL_INCLUDE_SEQUENCE_H
#define PPP_SRC_NASTL_INCLUDE_SEQUENCE_H

#include <ky/nastl/iterable.h>
#include <ky/nastl/any.h>

namespace ky::nastl {

class sequence;

class slice_ {
public:
private:
  friend class sequence;
  slice_(sequence &values, integer bIndex, integer eIndex);

  sequence &values_;
  integer bIndex_;
  integer eIndex_;
};

class sequence : public iterable {
public:
  virtual any &operator[](const integer &index) = 0;

  slice_ slice(const integer &bIndex, const integer &eIndex);
  slice_ slice(const integer &bIndex);

  [[nodiscard]] virtual integer size() const = 0;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_SEQUENCE_H
