#ifndef PPP_SRC_NASTL_IMPL_H
#define PPP_SRC_NASTL_IMPL_H

#include <ky/nastl/any.h>
#include <ky/nastl/string.h>
#include <ky/nastl/file.h>

namespace ky::nastl {

class impl {
public:
  static const std::string &get_value(const string &v) { return *v.value_; }

  static const std::string &get_std_string(const any &v) {
    return get_value(dynamic_cast<const string &>(v.as_object()));
  }

  static const char *get_c_str(const any &v) {
    return get_std_string(v).c_str();
  }

  static FILE *get_file(const file &v) {
    return v.file_;
  }
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_IMPL_H
