#ifndef PPP_SRC_NASTL_INCLUDE_STRING_H
#define PPP_SRC_NASTL_INCLUDE_STRING_H

#include <ky/nastl/any.h>

#include <string>

// find inspiration at https://docs.python.org/3/library/stdtypes.html?highlight=str#str

namespace ky::nastl {

class impl;
class visitor;

class string final : public object {
public:
  string();
  string(const char *);  // NOLINT(google-explicit-constructor)
  string(const any &);   // NOLINT(google-explicit-constructor)
  string(const string &);
  ~string() override;

  [[nodiscard]] any split(const any &sep, const any &max_splits) const;
  [[nodiscard]] any split(const any &sep) const;

  [[nodiscard]] any strip(const any &chars) const;
  [[nodiscard]] any strip() const;

  [[nodiscard]] iterator begin() const override;
  [[nodiscard]] iterator end() const override;
  [[nodiscard]] integer size() const override;

  any &operator[](const integer &) override;

  friend std::ostream &operator<<(std::ostream &, const string &);

private:
  void accept(visitor &) const override;

  [[nodiscard]] std::unique_ptr<object> clone() const override;
  [[nodiscard]] bool equals(const object &) const override;
  [[nodiscard]] bool less(const object &) const override;

  void replace(integer bIndex, integer eIndex, const sequence &) override;

  friend class ky::nastl::impl;
  std::shared_ptr<std::string> value_;
};

void print(const any &);

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_STRING_H
