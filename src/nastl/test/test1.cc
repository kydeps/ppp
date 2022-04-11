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
}
