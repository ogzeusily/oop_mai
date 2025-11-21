#pragma once

#include <concepts>
#include <iostream>
#include <type_traits>

namespace geometry {

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point {
public:
    using value_type = T;

    Point() = default;
    Point(T x, T y) noexcept;

    T x() const noexcept;
    T y() const noexcept;

    void set_x(T value) noexcept;
    void set_y(T value) noexcept;

    bool operator==(const Point& other) const noexcept = default;
    bool operator!=(const Point& other) const noexcept = default;

    double DistanceTo(const Point& other) const noexcept;

    template <Scalar U>
    friend std::istream& operator>>(std::istream& is, Point<U>& point);

    template <Scalar U>
    friend std::ostream& operator<<(std::ostream& os, const Point<U>& point);

private:
    T x_{};
    T y_{};
};

}  // namespace geometry

#include "point.ipp"
