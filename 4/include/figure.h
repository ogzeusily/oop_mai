#pragma once

#include <iostream>
#include <memory>
#include <string_view>

#include "point.h"

namespace geometry {

template <Scalar T>
class Figure {
public:
    using value_type = T;

    virtual ~Figure() = default;

    virtual void read(std::istream& is) = 0;
    virtual void print(std::ostream& os) const = 0;

    virtual Point<T> geometric_center() const = 0;
    virtual double surface() const = 0;
    virtual double perimeter() const = 0;

    virtual std::unique_ptr<Figure> clone() const = 0;

    explicit operator double() const {
        return surface();
    }

    friend std::istream& operator>>(std::istream& is, Figure& figure) {
        figure.read(is);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure& figure) {
        figure.print(os);
        return os;
    }
};

template <Scalar T>
std::string_view figure_name(const Figure<T>&) {
    return "Figure";
}

}  // namespace geometry
