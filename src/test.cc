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
  ASSERT_EQ("[3, 4]", str(l.slice(2, 4)));
  ASSERT_EQ("5", str(l[4]));

  // ASSERT_EQ("[1, 2, 3, 4, 5, 6, 7, 8, 9]", str(l({},{}))); // l[:]

  l.slice(2, 5) = list();
  ASSERT_EQ("[1, 2, 6, 7, 8, 9]", str(l));

  l.slice(2, 3) = list({10, 11, 12});
  ASSERT_EQ("[1, 2, 10, 11, 12, 7, 8, 9]", str(l));

  // TODO: test negative indices
  // TODO: define None
}

TEST(ppp, typed_lists) {  // NOLINT
  list_<int> l = {1, 2, 3};
  ASSERT_EQ("[1, 2, 3]", str(l));

  list_<list_<int>> ll;
  ll.append(l);
  ll.append(l);
  ll.append(l);
  ASSERT_EQ("[[1, 2, 3], [1, 2, 3], [1, 2, 3]]", str(ll));
}

TEST(ppp, negative_indices) {  // NOLINT
  list l = {1, 2, 3, 4, 5, 6};
  ASSERT_EQ("5", str(l[-2]));

  ASSERT_EQ("[3, 4]", str(l.slice(-4, -2)));

  ASSERT_THROW(l[6], IndexError);
  ASSERT_THROW(l[-7], IndexError);
}

TEST(ppp, list_methods) {  // NOLINT
  list l = {1, 2, 3};

  ASSERT_EQ("[1, 2]", str(l.slice(0, -1)));
  ASSERT_EQ("[2, 3]", str(l.slice(1)));
  ASSERT_EQ("[2, 3]", str(l.slice(-2)));

  l.extend(list({4, 5, 6}));
  ASSERT_EQ("[1, 2, 3, 4, 5, 6]", str(l));

  l.insert(0, -5);
  l.insert(-1, -5);
  l.insert(3, -5);
  ASSERT_EQ("[-5, 1, 2, -5, 3, 4, 5, -5, 6]", str(l));

  ASSERT_EQ("6", str(l.pop()));
  ASSERT_EQ("-5", str(l.pop(0)));
  ASSERT_EQ("-5", str(l.pop(2)));
  ASSERT_EQ("[1, 2, 3, 4, 5, -5]", str(l));
}

TEST(ppp, len) {  // NOLINT
  list l = {1, 2, 3, 4, 5, 6};

  ASSERT_EQ(6, len(l));
  ASSERT_EQ(2, len(l.slice(2, 4)));

  ASSERT_THROW(len(1), TypeError);
}

TEST(ppp, comprehension) { // NOLINT
  list l = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  // [x * 2 for x in l]
  // for 
  // [](auto x) { return x * 2 }
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
  x.slice(1, 2) = list({7, 7, 7});
  print(x.slice(1, 2));

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
