#include "math.eg.hpp"
#include <gtest/gtest.h>

TEST(MathTest, Add)
{
    EXPECT_EQ(eg::add(2, 3), 5);
    EXPECT_EQ(eg::add(-1, -1), -2);
}

TEST(MathTest, Mul)
{
    EXPECT_EQ(eg::mul(2, 3), 6);
    EXPECT_EQ(eg::mul(-1, 5), -5);
}
