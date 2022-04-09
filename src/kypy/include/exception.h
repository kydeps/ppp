#ifndef PPP_SRC_KYPY_INCLUDE_EXCEPTION_H
#define PPP_SRC_KYPY_INCLUDE_EXCEPTION_H

#include <exception>

namespace kypy {

class Exception : std::exception {};
class IndexError final : Exception {};
class TypeError final : Exception {};
class ValueError final : Exception {};
class NotImplemented final : Exception {};

}  // namespace kypy

#endif  // PPP_SRC_KYPY_INCLUDE_EXCEPTION_H
