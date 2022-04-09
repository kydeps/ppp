#include <ky/py/lib.h>

using namespace kypy;

int main() {
  auto x = list({1, 2, 3, list({4, 5})});
  print(x);

  x.extend(x);
  print(x);

  return 0;
}