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

print(x) is the same»

*/

int main() {
  auto l = list();
  l.append(1);

  list l2 = {2, 3};
  l.append(l2);

  print(l);

  for (auto x : l) {
    print(x);
  }

  // NOTE: if we did `var x = ...` then later .append does not work
  auto x = list({2, 3, list({5})});

  x[1] = 500;

  print(x);
  // auto y{x(33,5)};
  x.append(x(3,5));

  x.append(5);
  print(x);
}

/*
  - libraries
    - datetime
    - numpy
    - pandas
    - pygames
  - control the system
    - run process 
      - arguments from local vars
      - get return value (exit code)
      - read output of process
    - read files
      - parse files
      - parse csvs (with headers)
    - save csvs

  - more natural language
*/
