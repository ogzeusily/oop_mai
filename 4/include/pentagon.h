#pragma once

#include <array>
#include <memory>

#include "figure.h"

namespace geometry {

template <Scalar T>
class Pentagon : public Figure<T> {
public:
    using value_type = T;
    static constexpr std::size_t kVertexCount = 5;

    Pentagon();
    Pentagon(const Point<T>& center, T radius);

    Pentagon(const Pentagon& other);
    Pentagon& operator=(const Pentagon& other);

    Pentagon(Pentagon&& other) noexcept = default;
    Pentagon& operator=(Pentagon&& other) noexcept = default;

    ~Pentagon() override = default;

    Point<T> geometric_center() const override;
    double surface() const override;
    double perimeter() const override;

    std::unique_ptr<Figure<T>> clone() const override;

    bool operator==(const Pentagon& other) const noexcept;
    bool operator!=(const Pentagon& other) const noexcept;

    void read(std::istream& is) override;
    void print(std::ostream& os) const override;

private:
    void build_vertices();
    void copy_vertices(const Pentagon& other);

    Point<T> center_{};
    T radius_{};
    std::array<std::unique_ptr<Point<T>>, kVertexCount> vertices_;
};

}  // namespace geometry

<<<<<<< HEAD
#include "pentagon.ipp"
=======
#include "../src/pentagon.ipp"
>>>>>>> 6065f19 (add lab4)

