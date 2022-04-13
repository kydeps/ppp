#ifndef PPP_SRC_NASTL_INCLUDE_OBJECT_H
#define PPP_SRC_NASTL_INCLUDE_OBJECT_H

#include <ky/nastl/iterable.h>
#include <ky/nastl/sequence.h>

#include <iostream>

namespace ky::nastl {

class any;
class visitor;

class object : public sequence {
public:
  virtual ~object();

  [[nodiscard]] iterator begin() const override;
  [[nodiscard]] iterator end() const override;
  [[nodiscard]] integer size() const override;

  any &operator[](const integer &integer1) override;

protected:
  void replace(integer bIndex, integer eIndex, const sequence &) override;

private:
  friend class any;
  friend bool operator==(const any &x, const any &y);
  friend bool operator<(const any &x, const any &y);

  virtual void accept(visitor &) const = 0;

  [[nodiscard]] virtual std::unique_ptr<object> clone() const;
  [[nodiscard]] virtual bool equals(const object &) const;
  [[nodiscard]] virtual bool less(const object &) const;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_OBJECT_H
