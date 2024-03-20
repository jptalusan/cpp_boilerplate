#include <gtest/gtest.h>
#include "foo.h"
#include "sample2.h"
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  foo();
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, BasicAdd) {
  int a = 10;
  int b = 10;
  int c = add(a, b);
  EXPECT_EQ(20, c);
}

namespace {
// Tests the default c'tor.
  TEST(MyString, DefaultConstructor) {
    const MyString s;

    // Asserts that s.c_string() returns NULL.
    //
    // <TechnicalDetails>
    //
    // If we write NULL instead of
    //
    //   static_cast<const char *>(NULL)
    //
    // in this assertion, it will generate a warning on gcc 3.4.  The
    // reason is that EXPECT_EQ needs to know the types of its
    // arguments in order to print them when it fails.  Since NULL is
    // #defined as 0, the compiler will use the formatter function for
    // int to print it.  However, gcc thinks that NULL should be used as
    // a pointer, not an int, and therefore complains.
    //
    // The root of the problem is C++'s lack of distinction between the
    // integer number 0 and the null pointer constant.  Unfortunately,
    // we have to live with this fact.
    //
    // </TechnicalDetails>
    EXPECT_STREQ(nullptr, s.c_string());

    EXPECT_EQ(0u, s.Length());
  }

  const char kHelloString[] = "Hello, world!";
}
