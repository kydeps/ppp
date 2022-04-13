#ifndef PPP_SRC_NASTL_INCLUDE_LIST_H
#define PPP_SRC_NASTL_INCLUDE_LIST_H

#include <ky/nastl/object.h>

#include <vector>

namespace ky::nastl {

class list final : public object {
public:
  list();
  list(const list &);
  list(std::initializer_list<any>);
  ~list() override;

  void append(const any &);
  void extend(const any &);
  void insert(const any &index, const any &value);

  void clear();

  list copy();
  void reverse();

  any count(const any &value);
  any index(const any &value, const any &bIndex, const any &eIndex);
  any index(const any &value, const any &bIndex);
  any index(const any &value);
  void remove(const any &value);

  any pop(const any &index);
  any pop();

  void sort(const std::function<any(any)> &key, bool reverse);
  void sort(const std::function<any(any)> &key);
  void sort(bool reverse);
  void sort();

  [[nodiscard]] iterator begin() const override;
  [[nodiscard]] iterator end() const override;
  [[nodiscard]] integer size() const override;

  any &operator[](const integer &) override;

private:
  void accept(visitor &) const override;

  [[nodiscard]] std::unique_ptr<object> clone() const override;
  [[nodiscard]] bool equals(const object &) const override;
  [[nodiscard]] bool less(const object &) const override;

  void replace(integer bIndex, integer eIndex, const sequence &) override;

  std::shared_ptr<std::vector<any>> values_;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_LIST_H
