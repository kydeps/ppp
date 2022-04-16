#ifndef PPP_SRC_NASTL_INCLUDE_OBJECT_H
#define PPP_SRC_NASTL_INCLUDE_OBJECT_H

#include <ky/nastl/any.h>
#include <ky/nastl/iterable.h>
#include <ky/nastl/sequence.h>

#include <functional>
#include <iostream>

namespace ky::nastl {

class any;
class visitor;

class object : public sequence {
public:
  virtual ~object();

  // sequence and iterable

  [[nodiscard]] iterator begin() const override;
  [[nodiscard]] iterator end() const override;
  [[nodiscard]] integer size() const override;

  any &operator[](const integer &integer1) override;

  // string-like

  [[nodiscard]] virtual any split(const any &sep, const any &max_splits) const;
  [[nodiscard]] any split(const any &sep) const;

  [[nodiscard]] virtual any strip(const any &chars) const;
  [[nodiscard]] any strip() const;

  // list-like

  virtual void append(const any &);
  virtual void extend(const any &);
  virtual void insert(const any &index, const any &value);

  virtual void clear();

  virtual any copy();
  virtual void reverse();

  virtual any count(const any &value) const;
  virtual any index(const any &value, const any &bIndex, const any &eIndex)
      const;
  any index(const any &value, const any &bIndex) const;
  any index(const any &value) const;
  virtual void remove(const any &value);

  virtual any pop(const any &index);
  any pop();

  virtual void sort(const std::function<any(any)> &key, bool reverse);
  void sort(const std::function<any(any)> &key);
  void sort(bool reverse);
  void sort();

protected:
  void replace(integer bIndex, integer eIndex, const sequence &) override;

private:
  friend class any;
  friend bool operator==(const any &x, const any &y);
  friend bool operator<(const any &x, const any &y);

  virtual void accept(visitor &) const = 0;

  // TODO: remove
  [[nodiscard]] virtual std::unique_ptr<object> clone() const;
  [[nodiscard]] virtual bool equals(const object &) const;
  [[nodiscard]] virtual bool less(const object &) const;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_OBJECT_H
