#include <gtest/gtest.h>
#include "vector.h"
#include "triangle.h"
#include "rectangle.h"
#include "kvadrat.h"
#include <stdexcept>

// commit for pr
TEST(VectorTest, BasicOperations) {
    Vector v;
    EXPECT_TRUE(v.IsEmpty());
    
    Triangle* triangle = new Triangle(Point(0, 0), Point(3, 0), Point(1.5, 2.6));
    v.PushBack(triangle);
    
    EXPECT_EQ(v.Size(), 1u);
    EXPECT_FALSE(v.IsEmpty());
    
    delete triangle;
}

TEST(VectorTest, MultipleFigures) {
    Vector v;
    
    Triangle* triangle = new Triangle(Point(0, 0), Point(3, 0), Point(1.5, 2.6));
    Rectangle* rectangle = new Rectangle(Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3));
    Kvadrat* kvadrat = new Kvadrat(Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2));
    
    v.PushBack(triangle);
    v.PushBack(rectangle);
    v.PushBack(kvadrat);
    
    EXPECT_EQ(v.Size(), 3u);
    
    EXPECT_NE(v[0], nullptr);
    EXPECT_NE(v[1], nullptr);
    EXPECT_NE(v[2], nullptr);
    
    double totalArea = v.calculateTotalArea();
    EXPECT_GT(totalArea, 0.0);
    
    delete triangle;
    delete rectangle;
    delete kvadrat;
}

TEST(VectorTest, RemoveFigure) {
    Vector v;
    
    Triangle* triangle = new Triangle(Point(0, 0), Point(3, 0), Point(1.5, 2.6));
    Rectangle* rectangle = new Rectangle(Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3));
    
    v.PushBack(triangle);
    v.PushBack(rectangle);
    
    EXPECT_EQ(v.Size(), 2u);
    
    delete v[0];
    v.removeFigure(0);
    
    EXPECT_EQ(v.Size(), 1u);
    EXPECT_NE(v[0], nullptr);
    
    delete rectangle;
}

TEST(FigureTest, TriangleOperations) {
    Triangle triangle(Point(0, 0), Point(3, 0), Point(1.5, 2.6));
    
    double area = static_cast<double>(triangle);
    EXPECT_GT(area, 0.0);
    
    Triangle copy = triangle;
    EXPECT_TRUE(triangle == copy);
    
    Triangle moved = std::move(copy);
    EXPECT_TRUE(triangle == moved);
}

TEST(FigureTest, RectangleOperations) {
    Rectangle rectangle(Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3));
    
    double area = static_cast<double>(rectangle);
    EXPECT_GT(area, 0.0);
    
    Rectangle copy = rectangle;
    EXPECT_TRUE(rectangle == copy);
}

TEST(FigureTest, KvadratOperations) {
    Kvadrat kvadrat(Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2));
    
    double area = static_cast<double>(kvadrat);
    EXPECT_GT(area, 0.0);
    
    Kvadrat copy = kvadrat;
    EXPECT_TRUE(kvadrat == copy);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}