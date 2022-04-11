#include <ky/py/exception.h>
#include <ky/py/list.h>
#include <ky/py/string.h>

#include "impl.h"
#include "../nastl/include/string.h"

namespace kypy {

string::string(const char* value) : sequence() {
  while (*value) {
    impl_->values_.emplace_back(*value++);
  }
}

string operator+(const string& x, const string& y) {
  string result;
  result.slice(result.size()) = x;
  result.slice(result.size()) = y;
  return result;
}

}  // namespace kypy
