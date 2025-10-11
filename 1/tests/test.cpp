#include <gtest/gtest.h>
#include "separator.h"

TEST(SeparatorTest, PositiveNumbers) {
    EXPECT_EQ(10, separator(10, 2));
}

TEST(SeparatorTest, NegativeNumbers) {
    EXPECT_EQ(0, separator(-100, 0));
}

TEST(SeparatorTest, FirstNegativeSecondPositive) {
    EXPECT_EQ(0, separator(-100, 20)); 
}

TEST(SeparatorTest, FirstPositiveSecondNegative) {
    EXPECT_EQ(0, separator(100, -20));
}

TEST(SeparatorTest, Zeros) {
    EXPECT_EQ(0, separator(0, 0));
}

TEST(SeparatorTest, EdgeCases_ZeroSecond) {
    EXPECT_EQ(0, separator(0, 20));
}

TEST(SeparatorTest, EdgeCases_ZeroFirst) {
    EXPECT_EQ(0, separator(26, 0));
}

TEST(SeparatorTest, EdgeCases_NegativeSecond) {
    EXPECT_EQ(0, separator(0, -2)); 
}

TEST(SeparatorTest, EdgeCases_NegativeFirst) {
    EXPECT_EQ(0, separator(-32, 0));
}

TEST(SeparatorTest, LargeNumbers) {
    EXPECT_EQ(3000000, separator(1000000, 2000002));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}