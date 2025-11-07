#pragma once

#include <array>
#include <memory>

#include "figure.h"

namespace geometry {

template <Scalar T>
class Hexagon : public Figure<T> {
public:
    using value_type = T;
    static constexpr std::size_t kVertexCount = 6;

    Hexagon();
    Hexagon(const Point<T>& center, T radius);

    Hexagon(const Hexagon& other);
    Hexagon& operator=(const Hexagon& other);

    Hexagon(Hexagon&& other) noexcept = default;
    Hexagon& operator=(Hexagon&& other) noexcept = default;

    ~Hexagon() override = default;

    Point<T> geometric_center() const override;
    double surface() const override;
    double perimeter() const override;

    std::unique_ptr<Figure<T>> clone() const override;

    bool operator==(const Hexagon& other) const noexcept;
    bool operator!=(const Hexagon& other) const noexcept;

    void read(std::istream& is) override;
    void print(std::ostream& os) const override;

private:
    void build_vertices();
    void copy_vertices(const Hexagon& other);

    Point<T> center_{};
    T radius_{};
    std::array<std::unique_ptr<Point<T>>, kVertexCount> vertices_;
};

}  // namespace geometry

#include "../src/hexagon.ipp"

