#include <ky/py/lib.h>
#include <ky/py/str.h>

#include "impl.h"

#include <iostream>

namespace kypy {

void print(const any &x) {
  std::string result = std::get<std::string>(impl::impl_::get(str(x)));
  std::cout << result << std::endl;
}

}  // namespace kypy