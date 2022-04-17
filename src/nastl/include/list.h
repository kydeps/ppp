#ifndef PPP_SRC_NASTL_INCLUDE_LIST_H
#define PPP_SRC_NASTL_INCLUDE_LIST_H

#include <ky/nastl/object.h>

#include <functional>
#include <vector>

namespace ky::nastl {

class list final : public object {
public:
  list();
  list(const list &);
  list(std::initializer_list<any>);
  ~list() override;

  void append(const any &) override;
  void extend(const any &) override;
  void insert(const any &index, const any &value) override;

  void clear() override;

  [[nodiscard]] any copy() const override;
  void reverse() override;

  [[nodiscard]] any count(const any &value) const override;
  [[nodiscard]] any
  index(const any &value, const any &bIndex, const any &eIndex) const override;
  using object::index;
  void remove(const any &value) override;

  any pop(const any &index) override;
  using object::pop;

  void sort(const std::function<any(any)> &key, bool reverse) override;
  using object::sort;

  [[nodiscard]] iterator begin() const override;
  [[nodiscard]] iterator end() const override;
  [[nodiscard]] integer size() const override;

  any &operator[](const integer &) const override;

private:
  void accept(visitor &) const override;

  [[nodiscard]] bool equals(const object &) const override;
  [[nodiscard]] bool less(const object &) const override;
  [[nodiscard]] virtual std::unique_ptr<object> clone() const;

  void replace(integer bIndex, integer eIndex, const sequence &) override;

  std::shared_ptr<std::vector<any>> values_;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_LIST_H
