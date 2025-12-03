#include "point.h"
#include <cmath>

Point::Point() : x_(0), y_(0) {}

Point::Point(double x, double y) : x_(x), y_(y) {}

double Point::GetX() const {
    return x_;
}

double Point::GetY() const {
    return y_;
}

double Point::Distance(const Point& other) const {
    double dx = x_ - other.x_;
    double dy = y_ - other.y_;
    return std::sqrt(dx * dx + dy * dy);
}
