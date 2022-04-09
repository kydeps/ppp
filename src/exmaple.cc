#include <ky/py/lib.h>

using namespace kypy;

int main() {
  any x = list({1, 2, 3, list({4, 5})});
  print(x);
  return 0;
}