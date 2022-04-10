#include <ky/py/lib.h>

using namespace kypy;

int main() {
  // x = [1, 2, 3, [4, 5]]
  auto x = list({1, 2, 3, list({4, 5})});
  print(x);

  x.extend(x);
  print(x);

  // x[1:3] = []
  x.slice(1, 3) = list();
  print(x);

  return 0;
}