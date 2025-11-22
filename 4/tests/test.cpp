#include <gtest/gtest.h>
#include <numbers>

#include "figure_utils.h"
#include "hexagon.h"
#include "octagon.h"
#include "pentagon.h"
#include "vector.h"

using geometry::Hexagon;
using geometry::Octagon;
using geometry::Pentagon;
using geometry::Point;

TEST(RegularPolygonTest, AreaAndPerimeter) {
    const double radius = 2.0;
    const Pentagon<double> pent(Point<double>(0.0, 0.0), radius);
    const Hexagon<double> hex(Point<double>(1.0, -1.0), radius);

    const double pent_area_expected = 0.5 * 5.0 * radius * radius * std::sin(2.0 * std::numbers::pi_v<double> / 5.0);
    const double hex_perimeter_expected = 6.0 * 2.0 * radius * std::sin(std::numbers::pi_v<double> / 6.0);

    EXPECT_NEAR(pent.surface(), pent_area_expected, 1e-6);
    EXPECT_NEAR(hex.perimeter(), hex_perimeter_expected, 1e-6);
}

TEST(RegularPolygonTest, CopyAndEquality) {
    Octagon<double> base(Point<double>(2.0, 3.0), 1.5);
    Octagon<double> copy = base;

    EXPECT_EQ(base.geometric_center(), copy.geometric_center());
    EXPECT_TRUE(base == copy);

    Octagon<double> moved = std::move(copy);
    EXPECT_TRUE(base == moved);
}

TEST(ArrayTest, WorksWithSharedPointers) {
    using geometry::Figure;
    using FigurePtr = std::shared_ptr<Figure<double>>;

    containers::Vector<FigurePtr> figures;
    figures.PushBack(std::make_shared<Pentagon<double>>(Point<double>(0.0, 0.0), 1.0));
    figures.PushBack(std::make_shared<Hexagon<double>>(Point<double>(1.0, 1.0), 2.0));

    ASSERT_EQ(figures.Size(), 2);

    const double total = geometry::total_area(figures);
    EXPECT_GT(total, 0.0);

    figures.Erase(0, 1);
    EXPECT_EQ(figures.Size(), 1);
    EXPECT_NE(figures[0], nullptr);
}

TEST(ArrayTest, EmplaceBackForDerived) {
    containers::Vector<Hexagon<double>> hexagons;
    hexagons.EmplaceBack(Point<double>(0.0, 0.0), 1.0);
    hexagons.EmplaceBack(Point<double>(2.0, 2.0), 0.5);

    EXPECT_EQ(hexagons.Size(), 2);
    EXPECT_GT(hexagons[0].surface(), 0.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}