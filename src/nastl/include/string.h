#ifndef PPP_SRC_NASTL_INCLUDE_STRING_H
#define PPP_SRC_NASTL_INCLUDE_STRING_H

#include <ky/nastl/object.h>
#include <ky/nastl/sequence.h>

#include <string>

namespace ky::nastl {

class impl;
class visitor;

class string final : public sequence, public object {
public:
  string(const char *);  // NOLINT(google-explicit-constructor)
  string(const any &);   // NOLINT(google-explicit-constructor)
  string(const string &);
  ~string() override;

  [[nodiscard]] iterator begin() const override;
  [[nodiscard]] iterator end() const override;
  [[nodiscard]] integer size() const override;

  any &operator[](const integer &) override;

  void accept(visitor &) const override;

  [[nodiscard]] std::unique_ptr<object> clone() const override;
  [[nodiscard]] bool equals(const object &) const override;

  friend std::ostream &operator<<(std::ostream &, const string &);

private:
  friend class ky::nastl::impl;
  std::shared_ptr<std::string> value_;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_STRING_H
