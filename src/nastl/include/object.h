#ifndef PPP_SRC_NASTL_INCLUDE_OBJECT_H
#define PPP_SRC_NASTL_INCLUDE_OBJECT_H

#include <iostream>

#include <ky/nastl/iterable.h>
#include <ky/nastl/sequence.h>

namespace ky::nastl {

class any;
class visitor;

class object : public sequence {
public:
  virtual ~object();

private:
  friend class any;
  friend bool operator==(const any &x, const any &y);
  friend bool operator<(const any &x, const any &y);

  virtual void accept(visitor &) const = 0;

  [[nodiscard]] virtual std::unique_ptr<object> clone() const = 0;
  [[nodiscard]] virtual bool equals(const object &other) const = 0;
  [[nodiscard]] virtual bool less(const object &other) const = 0;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_OBJECT_H
