#pragma once

#include <iostream>
#include <iosfwd>
#include <memory>

#include "figure.h"
#include "vector.h"

namespace geometry {

template <Scalar T>
double total_area(const containers::Vector<std::shared_ptr<Figure<T>>>& figures);

template <Scalar T>
void print_figures(const containers::Vector<std::shared_ptr<Figure<T>>>& figures, std::ostream& os);

}  // namespace geometry

#include "figure_utils.ipp"
