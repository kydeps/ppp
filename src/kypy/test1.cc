#include <gtest/gtest.h>
#include <ky/py/list.h>
#include <ky/py/str.h>
#include <ky/py/var.h>

#include "impl.h"

using namespace kypy;

std::string to_string(var x) {
  return std::get<std::string>(impl::impl_::get(str(x)));
}

#define KYPY_ASSERT_EQ(x, y) kypy_assert_eq(x, y, #x " == " #y)
void kypy_assert_eq(var x, var y, const char *message) {
  ASSERT_EQ(x, y) << message << " | " << to_string(x) << " == " << to_string(y);
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

  l.slice(1,2) = list();
  KYPY_ASSERT_EQ("[0, 2, 3, 4, 5, 6, 7, 8, 9]", str(l));

  l.slice(1,1) = list({100});
  KYPY_ASSERT_EQ("[0, 100, 2, 3, 4, 5, 6, 7, 8, 9]", str(l));
}

TEST(kypy, list_append) {  // NOLINT
  list l = {1, 2, 3};
  l.append(4);
  KYPY_ASSERT_EQ("[1, 2, 3, 4]", str(l));
  l.append(list({1, 2}));
  KYPY_ASSERT_EQ("[1, 2, 3, 4, [1, 2]]", str(l));
}
