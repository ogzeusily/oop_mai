#pragma once

#include <cmath>
#include <memory>
#include <numbers>
#include <stdexcept>

namespace detail {

inline bool almost_equal(double lhs, double rhs, double eps = 1e-7) {
    return std::abs(lhs - rhs) <= eps;
}

}  // namespace detail

namespace geometry {

template <Scalar T>
Pentagon<T>::Pentagon() = default;

template <Scalar T>
Pentagon<T>::Pentagon(const Point<T>& center, T radius) : center_(center), radius_(radius) {
    if (!(radius_ > static_cast<T>(0))) {
        throw std::invalid_argument("Radius must be positive");
    }
    build_vertices();
}

template <Scalar T>
Pentagon<T>::Pentagon(const Pentagon& other)
    : Figure<T>(other), center_(other.center_), radius_(other.radius_) {
    copy_vertices(other);
}

template <Scalar T>
Pentagon<T>& Pentagon<T>::operator=(const Pentagon& other) {
    if (this != &other) {
        center_ = other.center_;
        radius_ = other.radius_;
        copy_vertices(other);
    }
    return *this;
}

template <Scalar T>
Point<T> Pentagon<T>::geometric_center() const {
    return center_;
}

template <Scalar T>
double Pentagon<T>::surface() const {
    const double r = static_cast<double>(radius_);
    const double angle = 2.0 * std::numbers::pi_v<double> / static_cast<double>(kVertexCount);
    return 0.5 * static_cast<double>(kVertexCount) * r * r * std::sin(angle);
}

template <Scalar T>
double Pentagon<T>::perimeter() const {
    const double r = static_cast<double>(radius_);
    const double side = 2.0 * r * std::sin(std::numbers::pi_v<double> / static_cast<double>(kVertexCount));
    return static_cast<double>(kVertexCount) * side;
}

template <Scalar T>
std::unique_ptr<Figure<T>> Pentagon<T>::clone() const {
    return std::make_unique<Pentagon>(*this);
}

template <Scalar T>
bool Pentagon<T>::operator==(const Pentagon& other) const noexcept {
    return center_ == other.center_ && detail::almost_equal(static_cast<double>(radius_), static_cast<double>(other.radius_));
}

template <Scalar T>
bool Pentagon<T>::operator!=(const Pentagon& other) const noexcept {
    return !(*this == other);
}

template <Scalar T>
void Pentagon<T>::read(std::istream& is) {
    T x{};
    T y{};
    T radius{};
    is >> x >> y >> radius;
    if (!is) {
        throw std::runtime_error("Failed to read pentagon data");
    }
    if (!(radius > static_cast<T>(0))) {
        throw std::invalid_argument("Radius must be positive");
    }
    center_ = Point<T>(x, y);
    radius_ = radius;
    build_vertices();
}

template <Scalar T>
void Pentagon<T>::print(std::ostream& os) const {
    os << "Pentagon: center=" << center_ << ", radius=" << radius_ << ", vertices=";
    for (std::size_t i = 0; i < kVertexCount; ++i) {
        os << ' ' << *vertices_[i];
    }
}

template <Scalar T>
void Pentagon<T>::build_vertices() {
    const double r = static_cast<double>(radius_);
    const double angle_step = 2.0 * std::numbers::pi_v<double> / static_cast<double>(kVertexCount);
    const double base_angle = std::numbers::pi_v<double> / static_cast<double>(kVertexCount);

    for (std::size_t i = 0; i < kVertexCount; ++i) {
        const double angle = base_angle + angle_step * static_cast<double>(i);
        const double x = static_cast<double>(center_.x()) + r * std::cos(angle);
        const double y = static_cast<double>(center_.y()) + r * std::sin(angle);
        vertices_[i] = std::make_unique<Point<T>>(static_cast<T>(x), static_cast<T>(y));
    }
}

template <Scalar T>
void Pentagon<T>::copy_vertices(const Pentagon& other) {
    for (std::size_t i = 0; i < kVertexCount; ++i) {
        vertices_[i] = std::make_unique<Point<T>>(*other.vertices_[i]);
    }
}

}  // namespace geometry


