#include <iostream>
#include <stdexcept>
#include <variant>
#include <functional>

class A {
public:
  int add(int x, int y) const { return x + y; }
  int sub(int x, int y) const { return x - y; }
  std::string name(const std::string &m) const { return m + ": A"; }
};

class B {
public:
  int mul(int x, int y) const { return x * y; }
  std::string name(const std::string &m) const { return m + ": B"; }
};

class C {
public:
  explicit C(A a) : data_(a) {}
  explicit C(B b) : data_(b) {}
  explicit C(int x) : data_(x) {}
  explicit C(float x) : data_(x) {}

  int add(int x, int y) const;
  int sub(int x, int y) const;
  int mul(int x, int y) const;
  std::string name(const std::string &m) const;

public:
  using data_t = std::variant<A, B, int, float>;

  data_t data_;
};

// https://stackoverflow.com/questions/257288/templated-check-for-the-existence-of-a-class-member-function
// https://eli.thegreenplace.net/2014/perfect-forwarding-and-universal-references-in-c

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

#define DISPATCH(method, ...) \
  dispatch_##method<decltype(method(__VA_ARGS__))>(data_, __VA_ARGS__)

DECLARE(add)
DECLARE(sub)
DECLARE(mul)
DECLARE(name)

int C::add(int x, int y) const { return DISPATCH(add, x, y); }
int C::sub(int x, int y) const { return DISPATCH(sub, x, y); }
int C::mul(int x, int y) const { return DISPATCH(mul, x, y); }

std::string C::name(const std::string &m) const { return DISPATCH(name, m); }

#define TRY(x)                          \
  try {                                 \
    x;                                  \
  } catch (std::exception & e) {        \
    std::cout << e.what() << std::endl; \
  }

int main() {
  C c1(A{});
  C c2(B{});
  C c3(0);

  TRY(std::cout << c1.add(2, 3) << std::endl);
  TRY(std::cout << c2.add(2, 3) << std::endl);
  TRY(std::cout << c3.add(2, 3) << std::endl);
  TRY(std::cout << c1.sub(2, 3) << std::endl);
  TRY(std::cout << c2.sub(2, 3) << std::endl);
  TRY(std::cout << c3.sub(2, 3) << std::endl);
  TRY(std::cout << c1.mul(2, 3) << std::endl);
  TRY(std::cout << c2.mul(2, 3) << std::endl);
  TRY(std::cout << c3.mul(2, 3) << std::endl);
  TRY(std::cout << c1.name("kamen") << std::endl);
  TRY(std::cout << c2.name("kamen") << std::endl);
  TRY(std::cout << c3.name("kamen") << std::endl);

  auto fp = &C::add;
  TRY(std::cout << std::invoke(fp, c1, 3, 4) << std::endl);
}
