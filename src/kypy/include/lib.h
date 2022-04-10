#ifndef PPP_SRC_KYPY_INCLUDE_LIB_H
#define PPP_SRC_KYPY_INCLUDE_LIB_H

#include <ky/py/any.h>
#include <ky/py/exception.h>
#include <ky/py/len.h>
#include <ky/py/list.h>
#include <ky/py/string.h>

namespace kypy {

void print(const any &x);

any str(const any &x);

std::ostream &operator<<(std::ostream &s, const any &x);

}  // namespace kypy

#endif  // PPP_SRC_KYPY_INCLUDE_LIB_H
