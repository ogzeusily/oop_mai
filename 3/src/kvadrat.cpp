#include "kvadrat.h"
#include <cmath>
#include <algorithm>


// commit for pr
Kvadrat::Kvadrat(const Point& p1, const Point& p2, const Point& p3, const Point& p4) 
    : Rectangle(p1, p2, p3, p4) {}

Kvadrat::Kvadrat(const Kvadrat& other) : Rectangle(other) {}

Kvadrat::Kvadrat(Kvadrat&& other) noexcept : Rectangle(std::move(other)) {}

Kvadrat& Kvadrat::operator=(const Kvadrat& other) {
    if (this != &other) {
        Rectangle::operator=(other);
    }
    return *this;
}

Kvadrat& Kvadrat::operator=(Kvadrat&& other) noexcept {
    if (this != &other) {
        Rectangle::operator=(std::move(other));
    }
    return *this;
}

bool Kvadrat::operator==(const Kvadrat& other) const {
    return Rectangle::operator==(other);
}

void Kvadrat::read(std::istream& is) {
    Rectangle::read(is);
}

void Kvadrat::print(std::ostream& os) const {
    os << "Kvadrat: " << getPoint1() << " " << getPoint2() << " " 
       << getPoint3() << " " << getPoint4();
}