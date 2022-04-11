#ifndef PPP_SRC_NASTL_INCLUDE_EXCEPTION_H
#define PPP_SRC_NASTL_INCLUDE_EXCEPTION_H

#include <stdexcept>

namespace ky::nastl {

class type_error : public std::runtime_error {
public:
  type_error(const char *message) : std::runtime_error(message) {}
};

}

#endif  // PPP_SRC_NASTL_INCLUDE_EXCEPTION_H
