#ifndef PPP_SRC_NASTL_INCLUDE_OBJECT_H
#define PPP_SRC_NASTL_INCLUDE_OBJECT_H

#include <iostream>

namespace ky::nastl {

class visitor;

class object {
public:
  virtual ~object();

  virtual void accept(visitor &) const = 0;

  [[nodiscard]] virtual std::unique_ptr<object> clone() const = 0;
  [[nodiscard]] virtual bool equals(const object &other) const = 0;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_OBJECT_H
