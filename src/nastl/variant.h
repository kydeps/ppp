#ifndef PPP_SRC_NASTL_VARIANT_H
#define PPP_SRC_NASTL_VARIANT_H

#include <stdexcept>

namespace ky::nastl {

#define DECLARE(method)                                                    \
  template <typename R, typename T, typename... Args>                      \
  R invoke_##method(T &&t, Args &&...args) {                               \
    if constexpr (requires { T{}.method(std::forward<Args>(args)...); }) { \
      return t.method(std::forward<Args>(args)...);                        \
    } else {                                                               \
      throw std::runtime_error(                                            \
          std::string() + "method " + #method + " not implemented for " +  \
          typeid(T).name());                                               \
    }                                                                      \
  }                                                                        \
                                                                           \
  template <typename R, typename D, typename... Args>                      \
  R dispatch_##method(D &&data, Args &&...args) {                          \
    return std::visit(                                                     \
        [&](const auto &t) {                                               \
          return invoke_##method<R>(t, std::forward<Args>(args)...);       \
        },                                                                 \
        data);                                                             \
  }

#define DISPATCH(v, method, ...) \
  dispatch_##method<decltype(method(__VA_ARGS__))>(v, __VA_ARGS__)

}  // namespace ky::nastl

#endif  // PPP_SRC_NASTL_VARIANT_H
