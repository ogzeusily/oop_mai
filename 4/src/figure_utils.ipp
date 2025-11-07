#pragma once

#include <ostream>

namespace geometry {

template <Scalar T>
double total_area(const containers::Vector<std::shared_ptr<Figure<T>>>& figures) {
    double total = 0.0;
    for (std::size_t i = 0; i < figures.Size(); ++i) {
        if (figures[i]) {
            total += static_cast<double>(*figures[i]);
        }
    }
    return total;
}

template <Scalar T>
void print_figures(const containers::Vector<std::shared_ptr<Figure<T>>>& figures, std::ostream& os) {
    for (std::size_t i = 0; i < figures.Size(); ++i) {
        if (!figures[i]) {
            os << i << ": <empty>\n";
            continue;
        }
        os << i << ": " << *figures[i] << " | center=" << figures[i]->geometric_center()
           << " | area=" << figures[i]->surface() << '\n';
    }
}

}  // namespace geometry


