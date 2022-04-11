#ifndef PPP_SRC_NASTL_INCLUDE_LIST_H
#define PPP_SRC_NASTL_INCLUDE_LIST_H

#include <ky/nastl/sequence.h>

#include <vector>

namespace ky::nastl {

class list final : public sequence, public object {
public:
  list();
  list(const list &);
  list(std::initializer_list<any>);
  ~list() override;

  [[nodiscard]] iterator begin() const override;
  [[nodiscard]] iterator end() const override;
  [[nodiscard]] integer size() const override;

  any &operator[](const integer &) override;

  void accept(visitor &) const override;

  [[nodiscard]] std::unique_ptr<object> clone() const override;
  [[nodiscard]] bool equals(const object &) const override;

private:
  std::shared_ptr<std::vector<any>> values_;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_LIST_H
