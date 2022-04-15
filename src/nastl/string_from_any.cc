#include <ky/nastl/list.h>
#include <ky/nastl/string.h>

#include "impl.h"
#include "to_std_string.h"

namespace ky::nastl {

string::string(const any &v)
    : value_(std::make_shared<std::string>(to_std_string(v))) {}

std::ostream &operator<<(std::ostream &s, const string &v) {
  return s << impl::get_value(v);
}

void print(const any &v) { std::cout << v << std::endl; }

}  // namespace ky::nastl