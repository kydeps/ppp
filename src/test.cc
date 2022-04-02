#include "lib.h"

/*
mapping:

python      ppp

[]          list()

[1, 2]      list({1, 2})

.append is the same

    for x in y:
        ...
becomes:
    for (auto x : y) {
        ...
    }

print(x) is the same

*/

int main() {
  auto l = list();
  l.append(1);

  auto l2 = list({2, 3});
  l.append(l2);

  print(l);

  for (auto x : l) {
    print(x);
  }

  print(list({l2, l, 3, l2}));
}
