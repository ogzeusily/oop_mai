#include "triangle.h"
#include <cmath>
#include <algorithm>

// commit for pr
Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) 
    : p1(p1), p2(p2), p3(p3) {}

Triangle::Triangle(const Triangle& other) 
    : p1(other.p1), p2(other.p2), p3(other.p3) {}

Triangle::Triangle(Triangle&& other) noexcept 
    : p1(std::move(other.p1)), p2(std::move(other.p2)), p3(std::move(other.p3)) {}

Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
    }
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other) noexcept {
    if (this != &other) {
        p1 = std::move(other.p1);
        p2 = std::move(other.p2);
        p3 = std::move(other.p3);
    }
    return *this;
}

bool Triangle::operator==(const Triangle& other) const {
    return p1 == other.p1 && p2 == other.p2 && p3 == other.p3;
}

void Triangle::read(std::istream& is) {
    is >> p1 >> p2 >> p3;
}

void Triangle::print(std::ostream& os) const {
    os << "Triangle: " << p1 << " " << p2 << " " << p3;
}

double Triangle::surface() const {
    double a = p1.distanceTo(p2);
    double b = p2.distanceTo(p3);
    double c = p3.distanceTo(p1);
    
    double s = (a + b + c) / 2.0;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

double Triangle::perimeter() const {
    double a = p1.distanceTo(p2);
    double b = p2.distanceTo(p3);
    double c = p3.distanceTo(p1);
    return a + b + c;
}