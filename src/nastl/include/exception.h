#ifndef PPP_SRC_NASTL_INCLUDE_EXCEPTION_H
#define PPP_SRC_NASTL_INCLUDE_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace ky::nastl {

class type_error : public std::runtime_error {
public:
  type_error() : std::runtime_error("type error") {}
};

class index_error : public std::runtime_error {
public:
  index_error() : std::runtime_error("index error") {}
};

class value_error : public std::runtime_error {
public:
  value_error() : std::runtime_error("value error") {}
};

class not_implemented : public std::runtime_error {
public:
  not_implemented() : std::runtime_error("not implemented") {}
  not_implemented(const std::string &message)
      : std::runtime_error("not implemented : " + message) {}
};

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_INCLUDE_EXCEPTION_H
