#ifndef PPP_SRC_KYPY_INCLUDE_VAR_H
#define PPP_SRC_KYPY_INCLUDE_VAR_H

#include <memory>

namespace kypy {

namespace impl {
class var_;
class impl_;
}

class list;

class var final {
public:
  var();
  var(int x);
  var(const char *x);
  var(const list &x);
  ~var();

  friend bool operator==(const var &x, const var &y);

  var *begin() const;
  var *end() const ;

private:
  friend class impl::impl_;

  std::shared_ptr<impl::var_> impl_;
};

extern const var None;

}  // namespace kypy

#endif  // PPP_SRC_KYPY_INCLUDE_VAR_H
