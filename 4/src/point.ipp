#pragma once

#include <cmath>

namespace geometry {

template <Scalar T>
Point<T>::Point(T x, T y) noexcept : x_(x), y_(y) {
}

template <Scalar T>
T Point<T>::x() const noexcept {
    return x_;
}

template <Scalar T>
T Point<T>::y() const noexcept {
    return y_;
}

template <Scalar T>
void Point<T>::set_x(T value) noexcept {
    x_ = value;
}

template <Scalar T>
void Point<T>::set_y(T value) noexcept {
    y_ = value;
}

template <Scalar T>
double Point<T>::DistanceTo(const Point& other) const noexcept {
    const double dx = static_cast<double>(x_) - static_cast<double>(other.x_);
    const double dy = static_cast<double>(y_) - static_cast<double>(other.y_);
    return std::hypot(dx, dy);
}

template <Scalar U>
std::istream& operator>>(std::istream& is, Point<U>& point) {
    return is >> point.x_ >> point.y_;
}

template <Scalar U>
std::ostream& operator<<(std::ostream& os, const Point<U>& point) {
    os << '(' << point.x_ << ", " << point.y_ << ')';
    return os;
}

}  // namespace geometry


