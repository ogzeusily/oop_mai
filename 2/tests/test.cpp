#include <gtest/gtest.h>
#include "decimal.h"
#include "vector.h"
#include <stdexcept>


TEST(VectorTest, BasicOperations) {
    Vector v1;
    EXPECT_TRUE(v1.IsEmpty());
    v1.PushBack(3);
    v1.PushBack(5);
    v1.PushBack(7);
    EXPECT_EQ(v1.Size(), 3u);
    EXPECT_EQ(v1.Data()[0], 3);
    EXPECT_EQ(v1.Data()[1], 5);
    EXPECT_EQ(v1.Data()[2], 7);
    v1.PopBack();
    EXPECT_EQ(v1.Size(), 2u);
    v1.Clear();
    EXPECT_TRUE(v1.IsEmpty());
}

TEST(VectorTest, CopyAndAssign) {
    Vector v1;
    v1.PushBack(1);
    v1.PushBack(2);
    Vector v2 = v1;
    EXPECT_EQ(v2.Size(), 2u);
    EXPECT_EQ(v2.Data()[0], 1);
    EXPECT_EQ(v2.Data()[1], 2);
}

TEST(VectorTest, InitializerList) {
    Vector v1 = {1, 2, 3};
    EXPECT_EQ(v1.Size(), 3u);
    EXPECT_EQ(v1.Data()[0], 1);
    EXPECT_EQ(v1.Data()[1], 2);
    EXPECT_EQ(v1.Data()[2], 3);
    Vector v2{4, 5};
    EXPECT_EQ(v2.Size(), 2u);
    EXPECT_EQ(v2.Data()[0], 4);
    EXPECT_EQ(v2.Data()[1], 5);
    Vector v3({1, 2});
    EXPECT_EQ(v3.Size(), 2u);
    EXPECT_EQ(v3.Data()[0], 1);
    EXPECT_EQ(v3.Data()[1], 2);
}

TEST(VectorTest, ConstructorWithValue) {
    Vector v(5, 10);
    EXPECT_EQ(v.Size(), 5u);
    for (size_t i = 0; i < v.Size(); ++i) {
        EXPECT_EQ(v.Data()[i], 10);
    }
}

TEST(VectorTest, MoveOperations) {
    Vector v1;
    v1.PushBack(1);
    v1.PushBack(2);
    v1.PushBack(3);
    Vector v2 = std::move(v1);
    EXPECT_EQ(v2.Size(), 3u);
    EXPECT_EQ(v2.Data()[0], 1);
    EXPECT_TRUE(v1.IsEmpty());
}

TEST(VectorTest, Accessors) {
    Vector v;
    v.PushBack(10);
    v.PushBack(20);
    EXPECT_EQ(v.Front(), 10);
    EXPECT_EQ(v.Back(), 20);
    unsigned char* data = v.Data();
    EXPECT_EQ(data[0], 10);
    EXPECT_EQ(data[1], 20);
}

TEST(VectorTest, CapacityAndReserve) {
    Vector v;
    EXPECT_GE(v.Capacity(), 0u);
    v.Reserve(100);
    EXPECT_GE(v.Capacity(), 100u);
    size_t old_cap = v.Capacity();
    v.Reserve(50);
    EXPECT_EQ(v.Capacity(), old_cap);
}

TEST(VectorTest, Modifiers) {
    Vector v = {1, 2, 3, 4, 5};
    v.Insert(2, 99);
    EXPECT_EQ(v.Size(), 6u);
    EXPECT_EQ(v.Data()[2], 99);
    EXPECT_EQ(v.Data()[3], 3);

    v.Erase(1, 3);
    EXPECT_EQ(v.Size(), 4u);
    EXPECT_EQ(v.Data()[0], 1);
    EXPECT_EQ(v.Data()[1], 3);
    EXPECT_EQ(v.Data()[2], 4);

    v.Resize(10, 7);
    EXPECT_EQ(v.Size(), 10u);
    EXPECT_EQ(v.Back(), 7);

    v.Resize(2, 0);
    EXPECT_EQ(v.Size(), 2u);
    EXPECT_EQ(v.Back(), 3);
}



TEST(DecimalTest, ConstructAndPrint) {
    Decimal d1("12345");
    Decimal d2({5,4,3,2,1});
    EXPECT_TRUE(d1.equals(d2));
}

TEST(DecimalTest, Add) {
    Decimal d1("123");
    Decimal d2("456");
    Decimal sum = Decimal::add(d1, d2);
    Decimal expected("579");
    EXPECT_TRUE(sum.equals(expected));
    Decimal d3("13");
    Decimal d4("100000000000000");
    Decimal sum1 = Decimal::add(d3, d4);
    Decimal expected1("100000000000013");
    EXPECT_TRUE(sum1.equals(expected1));
}

TEST(DecimalTest, Subtract) {
    Decimal d1("1000");
    Decimal d2("1");
    Decimal diff = Decimal::subtract(d1, d2);
    Decimal expected("999");
    EXPECT_TRUE(diff.equals(expected));

    Decimal d3("63");
    Decimal d4("19");
    Decimal diff1 = Decimal::subtract(d3, d4);
    Decimal expected1("44");
    EXPECT_TRUE(diff1.equals(expected1));
}

TEST(DecimalTest, Compare) {
    Decimal d1("123");
    Decimal d2("456");
    EXPECT_TRUE(d2.is_greater(d1));
    EXPECT_TRUE(d1.is_less(d2));
    EXPECT_FALSE(d1.is_greater(d2));
    EXPECT_FALSE(d2.is_less(d1));
    EXPECT_TRUE(d1.equals(Decimal("123")));

    Decimal d3("123");
    Decimal d4("123");
    EXPECT_FALSE(d4.is_greater(d3));
    EXPECT_FALSE(d3.is_less(d4));
    EXPECT_FALSE(d3.is_greater(d4));
    EXPECT_FALSE(d4.is_less(d3));
}

TEST(DecimalTest, SubtractThrowsIfNegative) {
    Decimal d1("5");
    Decimal d2("10");
    EXPECT_THROW(Decimal::subtract(d1, d2), std::invalid_argument);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}