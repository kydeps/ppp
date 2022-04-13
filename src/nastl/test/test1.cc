#include <gtest/gtest.h>
#include <ky/nastl/nastl.h>

using namespace ky::nastl;

#define NASTL_ASSERT_EQ(x, y) nastl_assert_eq(x, y, #x " == " #y)
void nastl_assert_eq(const any& x, const any& y, const char* message) {
  ASSERT_EQ(x, y) << message << " | " << x << " == " << y;
}

TEST(nastl, object) {  // NOLINT'
  ASSERT_EQ(2 + 2, 4);

  auto l = list({1, 2, 3});
  NASTL_ASSERT_EQ("[1, 2, 3]", string(l));
  l.slice(1, 2) = list({201, 202});
  NASTL_ASSERT_EQ("[1, 201, 202, 3]", string(l));
}

TEST(nastl, list_index) {  // NOLINT
  auto l = list({1, 2, 3});

  NASTL_ASSERT_EQ("1", string(l[0]));
  NASTL_ASSERT_EQ("2", string(l[1]));
  NASTL_ASSERT_EQ("3", string(l[-1]));
  NASTL_ASSERT_EQ("2", string(l[-2]));
  ASSERT_THROW(l[3], index_error);
  ASSERT_THROW(l[-4], index_error);
}

TEST(nastl, list) {  // NOLINT
  NASTL_ASSERT_EQ("[]", string(list()));
  NASTL_ASSERT_EQ("[1]", string(list({1})));
  NASTL_ASSERT_EQ("[1, 2, 3]", string(list({1, 2, 3})));
  NASTL_ASSERT_EQ("[1, [2, 2], 3]", string(list({1, list({2, 2}), 3})));
}

TEST(nastl, list_slice) {  // NOLINT
  list l = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  NASTL_ASSERT_EQ("[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]", string(l));

  l.slice(1, 2) = list();
  NASTL_ASSERT_EQ("[0, 2, 3, 4, 5, 6, 7, 8, 9]", string(l));

  l.slice(1, 1) = list({100});
  NASTL_ASSERT_EQ("[0, 100, 2, 3, 4, 5, 6, 7, 8, 9]", string(l));
}

TEST(nastl, list_append) {  // NOLINT
  list l = {1, 2, 3};
  l.append(4);
  NASTL_ASSERT_EQ("[1, 2, 3, 4]", string(l));
  l.append(list({1, 2}));
  NASTL_ASSERT_EQ("[1, 2, 3, 4, [1, 2]]", string(l));
}

TEST(nastl, list_extend) {  // NOLINT
  list l = {1, 2, 3};
  l.extend(list({4}));
  NASTL_ASSERT_EQ("[1, 2, 3, 4]", string(l));
  l.extend(list({5, 6}));
  NASTL_ASSERT_EQ("[1, 2, 3, 4, 5, 6]", string(l));
}

TEST(nastl, list_insert) {  // NOLINT
  list l = {1, 2, 3};
  l.insert(0, 100);
  NASTL_ASSERT_EQ("[100, 1, 2, 3]", string(l));
  l.insert(l.size(), 100);
  NASTL_ASSERT_EQ("[100, 1, 2, 3, 100]", string(l));
  l.insert(2, 100);
  NASTL_ASSERT_EQ("[100, 1, 100, 2, 3, 100]", string(l));
}

TEST(nastl, list_remove) {  // NOLINT
  list l = {1, 2, 3, 4, 5};
  l.remove(2);
  NASTL_ASSERT_EQ("[1, 3, 4, 5]", string(l));
  ASSERT_THROW(l.remove(6), value_error);
}

TEST(nastl, list_pop) {  // NOLINT
  list l = {1, 2, 3, 4, 5};
  NASTL_ASSERT_EQ(1, l.pop(0));
  NASTL_ASSERT_EQ(5, l.pop());
  NASTL_ASSERT_EQ(3, l.pop(1));
  NASTL_ASSERT_EQ("[2, 4]", string(l));
}

TEST(nastl, list_clear) {  // NOLINT
  list l = {1, 2, 3, 4, 5};
  l.clear();
  NASTL_ASSERT_EQ("[]", string(l));
}

TEST(nastl, list_count) {  // NOLINT
  list l = {1, 2, 3, 4, 5, 1, 2, 3, 4, 1, 2, 3, 1, 2, 1};
  NASTL_ASSERT_EQ("5", string(l.count(1)));
  NASTL_ASSERT_EQ("4", string(l.count(2)));
  NASTL_ASSERT_EQ("3", string(l.count(3)));
  NASTL_ASSERT_EQ("2", string(l.count(4)));
  NASTL_ASSERT_EQ("1", string(l.count(5)));
  NASTL_ASSERT_EQ("0", string(l.count(6)));
}

TEST(nastl, list_copy) {  // NOLINT
  list l = {1, 2, 3, 4, 5};
  list ll = l.copy();
  l.clear();
  NASTL_ASSERT_EQ("[]", string(l));
  NASTL_ASSERT_EQ("[1, 2, 3, 4, 5]", string(ll));
}

TEST(nastl, list_reverse) {  // NOLINT
  list l = {1, 2, 3, 4, 5};
  l.reverse();
  NASTL_ASSERT_EQ("[5, 4, 3, 2, 1]", string(l));
}

TEST(nastl, list_sort) {  // NOLINT
  list l = {1, 2, 3, 4, 5};
  l.reverse();
  NASTL_ASSERT_EQ("[5, 4, 3, 2, 1]", string(l));
  l.sort();
  NASTL_ASSERT_EQ("[1, 2, 3, 4, 5]", string(l));
  l.sort(true);
  NASTL_ASSERT_EQ("[5, 4, 3, 2, 1]", string(l));

  list ll = {
      list({1, 2, 3}),
      list({1, 2}),
      list({1}),
  };
  NASTL_ASSERT_EQ("[[1, 2, 3], [1, 2], [1]]", string(ll));
  ll.sort(lambda(x, x.size()));
//  ll.sort([](auto key) { return key.size(); });
  NASTL_ASSERT_EQ("[[1], [1, 2], [1, 2, 3]]", string(ll));
  ll.sort(lambda(x, x.size()), true);
  NASTL_ASSERT_EQ("[[1, 2, 3], [1, 2], [1]]", string(ll));
}

TEST(nastl, strings) {  // NOLINT
  string s = "12345";
  NASTL_ASSERT_EQ("12345", s);
  // TODO(kamen): should we have that string(...) below?
  s.slice(1,3) = string("foo");
  NASTL_ASSERT_EQ("1foo45", s);
  any ss = s;
  ss = ss + ss;
  NASTL_ASSERT_EQ("1foo451foo45", ss);
}