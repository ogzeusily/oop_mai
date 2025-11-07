#pragma once

#include <array>
#include <memory>

#include "figure.h"

namespace geometry {

template <Scalar T>
class Octagon : public Figure<T> {
public:
    using value_type = T;
    static constexpr std::size_t kVertexCount = 8;

    Octagon();
    Octagon(const Point<T>& center, T radius);

    Octagon(const Octagon& other);
    Octagon& operator=(const Octagon& other);

    Octagon(Octagon&& other) noexcept = default;
    Octagon& operator=(Octagon&& other) noexcept = default;

    ~Octagon() override = default;

    Point<T> geometric_center() const override;
    double surface() const override;
    double perimeter() const override;

    std::unique_ptr<Figure<T>> clone() const override;

    bool operator==(const Octagon& other) const noexcept;
    bool operator!=(const Octagon& other) const noexcept;

    void read(std::istream& is) override;
    void print(std::ostream& os) const override;

private:
    void build_vertices();
    void copy_vertices(const Octagon& other);

    Point<T> center_{};
    T radius_{};
    std::array<std::unique_ptr<Point<T>>, kVertexCount> vertices_;
};

}  // namespace geometry

<<<<<<< HEAD
#include "octagon.ipp"
=======
#include "../src/octagon.ipp"
>>>>>>> 6065f19 (add lab4)

