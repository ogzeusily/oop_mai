#pragma once
#include "figure.h"
#include "point.h"

// commit for pr
class Rectangle : public Figure {
public:
    Rectangle() = delete;
    Rectangle(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;
    
    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;
    bool operator==(const Rectangle& other) const;
    
    void read(std::istream& is) override;
    void print(std::ostream& os) const override;
    
    double surface() const override;
    double perimeter() const override;
    
    const Point& getPoint1() const { return p1; }
    const Point& getPoint2() const { return p2; }
    const Point& getPoint3() const { return p3; }
    const Point& getPoint4() const { return p4; }
    
    void setPoint1(const Point& p) { p1 = p; }
    void setPoint2(const Point& p) { p2 = p; }
    void setPoint3(const Point& p) { p3 = p; }
    void setPoint4(const Point& p) { p4 = p; }

private:
    Point p1, p2, p3, p4;
};