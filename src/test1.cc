#include <gtest/gtest.h>
#include <ky/py/any.h>
#include <ky/py/exception.h>
#include <ky/py/len.h>
#include <ky/py/lib.h>
#include <ky/py/list.h>
#include <ky/py/string.h>

#include "kypy/impl.h"

using namespace kypy;

#define KYPY_ASSERT_EQ(x, y) kypy_assert_eq(x, y, #x " == " #y)
void kypy_assert_eq(const any& x, const any& y, const char* message) {
  ASSERT_EQ(x, y) << message << " | " << x << " == " << y;
}

TEST(kypy, var) {  // NOLINT
  KYPY_ASSERT_EQ("1", str(1));
  KYPY_ASSERT_EQ("-1", str(-1));
  KYPY_ASSERT_EQ("foo", str("foo"));
  KYPY_ASSERT_EQ("", str(None));
}

TEST(kypy, list) {  // NOLINT
  KYPY_ASSERT_EQ("[]", str(list()));
  KYPY_ASSERT_EQ("[1]", str(list({1})));
  KYPY_ASSERT_EQ("[1, 2, 3]", str(list({1, 2, 3})));
  KYPY_ASSERT_EQ("[1, [2, 2], 3]", str(list({1, list({2, 2}), 3})));
}

TEST(kypy, list_slice) {  // NOLINT
  list l = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  KYPY_ASSERT_EQ("[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]", str(l));

  l.slice(1, 2) = list();
  KYPY_ASSERT_EQ("[0, 2, 3, 4, 5, 6, 7, 8, 9]", str(l));

  l.slice(1, 1) = list({100});
  KYPY_ASSERT_EQ("[0, 100, 2, 3, 4, 5, 6, 7, 8, 9]", str(l));
}

TEST(kypy, list_append) {  // NOLINT
  list l = {1, 2, 3};
  l.append(4);
  KYPY_ASSERT_EQ("[1, 2, 3, 4]", str(l));
  l.append(list({1, 2}));
  KYPY_ASSERT_EQ("[1, 2, 3, 4, [1, 2]]", str(l));
}

TEST(kypy, list_extend) {  // NOLINT
  list l = {1, 2, 3};
  l.extend(list({4}));
  KYPY_ASSERT_EQ("[1, 2, 3, 4]", str(l));
  l.extend(list({5, 6}));
  KYPY_ASSERT_EQ("[1, 2, 3, 4, 5, 6]", str(l));
}

TEST(kypy, list_insert) {  // NOLINT
  list l = {1, 2, 3};
  l.insert(0, 100);
  KYPY_ASSERT_EQ("[100, 1, 2, 3]", str(l));
  l.insert(len(l), 100);
  KYPY_ASSERT_EQ("[100, 1, 2, 3, 100]", str(l));
  l.insert(2, 100);
  KYPY_ASSERT_EQ("[100, 1, 100, 2, 3, 100]", str(l));
}

TEST(kypy, list_remove) {  // NOLINT
  list l = {1, 2, 3, 4, 5};
  l.remove(2);
  KYPY_ASSERT_EQ("[1, 3, 4, 5]", str(l));
  ASSERT_THROW(l.remove(6), ValueError);
}

TEST(kypy, list_pop) {  // NOLINT
  list l = {1, 2, 3, 4, 5};
  KYPY_ASSERT_EQ(1, l.pop(0));
  KYPY_ASSERT_EQ(5, l.pop());
  KYPY_ASSERT_EQ(3, l.pop(1));
  KYPY_ASSERT_EQ("[2, 4]", str(l));
}

TEST(kypy, list_clear) {  // NOLINT
  list l = {1, 2, 3, 4, 5};
  l.clear();
  KYPY_ASSERT_EQ("[]", str(l));
}

TEST(kypy, list_count) {  // NOLINT
  list l = {1, 2, 3, 4, 5, 1, 2, 3, 4, 1, 2, 3, 1, 2, 1};
  KYPY_ASSERT_EQ("5", str(l.count(1)));
  KYPY_ASSERT_EQ("4", str(l.count(2)));
  KYPY_ASSERT_EQ("3", str(l.count(3)));
  KYPY_ASSERT_EQ("2", str(l.count(4)));
  KYPY_ASSERT_EQ("1", str(l.count(5)));
  KYPY_ASSERT_EQ("0", str(l.count(6)));
}

TEST(kypy, list_copy) {  // NOLINT
  list l = {1, 2, 3, 4, 5};
  list ll = l.copy();
  l.clear();
  KYPY_ASSERT_EQ("[]", str(l));
  KYPY_ASSERT_EQ("[1, 2, 3, 4, 5]", str(ll));
}

TEST(kypy, list_reverse) {  // NOLINT
  list l = {1, 2, 3, 4, 5};
  l.reverse();
  KYPY_ASSERT_EQ("[5, 4, 3, 2, 1]", str(l));
}

TEST(kypy, list_sort) {  // NOLINT
  list l = {1, 2, 3, 4, 5};
  l.reverse();
  KYPY_ASSERT_EQ("[5, 4, 3, 2, 1]", str(l));
  l.sort();
  KYPY_ASSERT_EQ("[1, 2, 3, 4, 5]", str(l));
  l.sort(true);
  KYPY_ASSERT_EQ("[5, 4, 3, 2, 1]", str(l));

  list ll = {
      list({1, 2, 3}),
      list({1, 2}),
      list({1}),
  };
  KYPY_ASSERT_EQ("[[1, 2, 3], [1, 2], [1]]", str(ll));
  ll.sort(lambda(x, len(x)));
  //  ll.sort([](auto key) { return len(key); });
  KYPY_ASSERT_EQ("[[1], [1, 2], [1, 2, 3]]", str(ll));
  ll.sort(lambda(x, len(x)), true);
  KYPY_ASSERT_EQ("[[1, 2, 3], [1, 2], [1]]", str(ll));
}

TEST(kypy, strings) {  // NOLINT
  string s = "12345";
  KYPY_ASSERT_EQ("12345", s);
  // TODO(kamen): should we have that string(...) below?
  s.slice(1,3) = string("foo");
  KYPY_ASSERT_EQ("1foo45", s);
  s = s + s;
  KYPY_ASSERT_EQ("1foo451foo45", s);
}