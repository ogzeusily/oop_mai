#include "rectangle.h"
#include <cmath>
#include <algorithm>


Rectangle::Rectangle(const Point& p1, const Point& p2, const Point& p3, const Point& p4) 
    : p1(p1), p2(p2), p3(p3), p4(p4) {}

Rectangle::Rectangle(const Rectangle& other) 
    : p1(other.p1), p2(other.p2), p3(other.p3), p4(other.p4) {}

Rectangle::Rectangle(Rectangle&& other) noexcept 
    : p1(std::move(other.p1)), p2(std::move(other.p2)), 
      p3(std::move(other.p3)), p4(std::move(other.p4)) {}

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
        p4 = other.p4;
    }
    return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
        p4 = std::move(other.p4);
    }
    return *this;
}

bool Rectangle::operator==(const Rectangle& other) const {
    return p1 == other.p1 && p2 == other.p2 && 
           p3 == other.p3 && p4 == other.p4;
}

void Rectangle::read(std::istream& is) {
    is >> p1 >> p2 >> p3 >> p4;
}

void Rectangle::print(std::ostream& os) const {
    os << "Rectangle: " << p1 << " " << p2 << " " << p3 << " " << p4;
}

double Rectangle::surface() const {
    double x1 = p1.getX(), y1 = p1.getY();
    double x2 = p2.getX(), y2 = p2.getY();
    double x3 = p3.getX(), y3 = p3.getY();
    double x4 = p4.getX(), y4 = p4.getY();
    
    double area = 0.5 * std::abs((x1*y2 + x2*y3 + x3*y4 + x4*y1) - (y1*x2 + y2*x3 + y3*x4 + y4*x1));
    return area;
}

double Rectangle::perimeter() const {
    double a = p1.distanceTo(p2);
    double b = p2.distanceTo(p3);
    double c = p3.distanceTo(p4);
    double d = p4.distanceTo(p1);
    return a + b + c + d;
}