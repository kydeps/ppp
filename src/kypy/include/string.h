#ifndef PPP_SRC_KYPY_INCLUDE_STRING_H
#define PPP_SRC_KYPY_INCLUDE_STRING_H

#include <ky/py/any.h>
#include <ky/py/sequence.h>

namespace kypy {

class string final : public sequence {
public:
  string() = default;
  string(const char *value);

  friend string operator+(const string &x, const string &y);
};

}  // namespace kypy

#endif  // PPP_SRC_KYPY_INCLUDE_STRING_H
