#ifndef PPP_SRC_NASTL_INCLUDE_FILE_H
#define PPP_SRC_NASTL_INCLUDE_FILE_H

#include <ky/nastl/object.h>

namespace ky::nastl {

// https://docs.python.org/3/library/functions.html?highlight=open#open

class file final : public object {
public:
  explicit file(const any &filename);
  file(const any &filename, const any &mode);
  ~file() override;

  void accept(visitor &) const override;

  [[nodiscard]] iterator begin() const override;
  [[nodiscard]] iterator end() const override;

private:
  friend class impl;
  FILE* file_;
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_FILE_H
