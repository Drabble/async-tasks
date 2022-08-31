#include <gtest/gtest.h>
#include "library.h"

// Demonstrate some basic assertions.
TEST(AsyncTask, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
    // Run lib.h
    hello();
}