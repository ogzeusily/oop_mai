#include <iostream>
#include <memory>

#include "figure_utils.h"
#include "hexagon.h"
#include "octagon.h"
#include "pentagon.h"
#include "vector.h"

using geometry::Figure;
using geometry::Hexagon;
using geometry::Octagon;
using geometry::Pentagon;
using geometry::Point;

int main() {
    using FigurePtr = std::shared_ptr<Figure<double>>;
    containers::Vector<FigurePtr> figures;

    auto pentagon = std::make_shared<Pentagon<double>>(Point<double>(0.0, 0.0), 2.0);
    figures.PushBack(pentagon);

    auto hexagon = std::make_shared<Hexagon<double>>(Point<double>(1.0, 1.0), 1.5);
    figures.PushBack(hexagon);

    auto octagon = std::make_shared<Octagon<double>>(Point<double>(2.0, 2.0), 1.0);
    figures.PushBack(octagon);

    for (size_t i = 0; i < figures.Size(); ++i) {
        std::cout << *figures[i] << std::endl;
    }

    for (size_t i = 0; i < figures.Size(); ++i) {
        std::cout << static_cast<double>(*figures[i]) << std::endl;
    }

    std::cout << geometry::total_area(figures) << std::endl;

    Pentagon<double> pentagonCopy = *pentagon;

    bool areEqual = (*pentagon == pentagonCopy);

    Pentagon<double> pentagonMoved = std::move(pentagonCopy);

    std::cout << figures.Size() << std::endl;

    if (figures.Size() > 1) {
        figures.Erase(1, 2);
    }

    for (size_t i = 0; i < figures.Size(); ++i) {
        std::cout << *figures[i] << std::endl;
    }

    std::cout << geometry::total_area(figures) << std::endl;

    containers::Vector<Hexagon<double>> hexagons;
    hexagons.EmplaceBack(Point<double>(0.0, 0.0), 1.0);
    hexagons.EmplaceBack(Point<double>(2.5, 1.5), 1.2);

    std::cout << "\nПример массива наследников (Hexagon): количество = " << hexagons.Size() << std::endl;
    for (std::size_t i = 0; i < hexagons.Size(); ++i) {
        std::cout << "hexagons[" << i << "] площадь = " << hexagons[i].surface() << std::endl;
    }

    return 0;
}