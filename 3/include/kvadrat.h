#pragma once
#include "rectangle.h"
#include "point.h"

// commit for pr
class Kvadrat : public Figure {
public:
    Kvadrat() = delete;
    Kvadrat(const Point& p1, const Point& p2, const Point& p3, const Point& p4);
    Kvadrat(const Kvadrat& other);
    Kvadrat(Kvadrat&& other) noexcept;
    
    Kvadrat& operator=(const Kvadrat& other);
    Kvadrat& operator=(Kvadrat&& other) noexcept;
    bool operator==(const Kvadrat& other) const;
    
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