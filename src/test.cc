#include <gtest/gtest.h>

#include <ppp/ppp.h>

using namespace ppp;

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

TEST(ppp, lists) {  // NOLINT
  ASSERT_EQ("[]", str(list()));
  ASSERT_EQ("[1, 2, 3]", str(list({1, 2, 3})));

  list l = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  ASSERT_EQ("[1, 2, 3, 4, 5, 6, 7, 8, 9]", str(l));
  ASSERT_EQ("[3, 4]", str(l(2, 4)));
  ASSERT_EQ("5", str(l[4]));

  //ASSERT_EQ("[1, 2, 3, 4, 5, 6, 7, 8, 9]", str(l({},{}))); // l[:]

  l(2, 5) = list();
  ASSERT_EQ("[1, 2, 6, 7, 8, 9]", str(l));

  l(2, 3) = list({10, 11, 12});
  ASSERT_EQ("[1, 2, 10, 11, 12, 7, 8, 9]", str(l));

  // TODO: test negative indices
  // TODO: define None
}

TEST(ppp, common) {  // NOLINT
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
  x(1, 2) = list({7, 7, 7});
  print(x(1, 2));

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
