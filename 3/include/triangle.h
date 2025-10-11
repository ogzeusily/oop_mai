#pragma once
#include "figure.h"
#include "point.h"

class Triangle : public Figure {
public:
    Triangle() = delete;
    Triangle(const Point& p1, const Point& p2, const Point& p3);
    Triangle(const Triangle& other);
    Triangle(Triangle&& other) noexcept;
    
    Triangle& operator=(const Triangle& other);
    Triangle& operator=(Triangle&& other) noexcept;
    bool operator==(const Triangle& other) const;
    
    void read(std::istream& is) override;
    void print(std::ostream& os) const override;
    
    double surface() const override;
    double perimeter() const override;
    
    const Point& getPoint1() const { return p1; }
    const Point& getPoint2() const { return p2; }
    const Point& getPoint3() const { return p3; }
    
    void setPoint1(const Point& p) { p1 = p; }
    void setPoint2(const Point& p) { p2 = p; }
    void setPoint3(const Point& p) { p3 = p; }

private:
    Point p1, p2, p3;
};