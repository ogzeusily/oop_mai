#pragma once

#include <cmath>

namespace geometry::detail {

inline bool almost_equal(double lhs, double rhs, double eps = 1e-7) {
    return std::abs(lhs - rhs) <= eps;
}

}  // namespace geometry::detail


