#include "figure_array.hpp"
#include "pentagon.hpp"
#include "rhombus.hpp"
#include "trapezoid.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <sstream>

namespace {

constexpr double kTolerance = 1e-6;

}  // namespace

TEST(TrapezoidTest, AreaAndCenterFromInput) {
    Trapezoid trapezoid;
    std::stringstream input("0 0 4 0 3 2 1 2");
    input >> trapezoid;

    EXPECT_DOUBLE_EQ(trapezoid.Area(), 6.0);
    const Point center = trapezoid.Center();
    EXPECT_NEAR(center.x, 2.0, kTolerance);
    EXPECT_NEAR(center.y, 0.8888888888888888, kTolerance);
}

TEST(RhombusTest, EqualityAndClone) {
    Rhombus rhombusA;
    std::stringstream input("0 0 2 1 4 0 2 -1");
    input >> rhombusA;

    EXPECT_DOUBLE_EQ(rhombusA.Area(), 4.0);
    const Point center = rhombusA.Center();
    EXPECT_NEAR(center.x, 2.0, kTolerance);
    EXPECT_NEAR(center.y, 0.0, kTolerance);

    auto rhombusB = rhombusA.Clone();
    EXPECT_TRUE(rhombusA == *rhombusB);
}

TEST(PentagonTest, AreaAndInequality) {
    Pentagon pentagon;
    std::stringstream input("0 0 2 0 3 1 1.5 3 0 1");
    input >> pentagon;
    EXPECT_NEAR(pentagon.Area(), 5.5, kTolerance);

    auto other = pentagon.Clone();
    std::stringstream differentInput("0 0 2 0 3 2 1 3 0 1");
    Pentagon pentagonDifferent;
    differentInput >> pentagonDifferent;
    EXPECT_FALSE(pentagonDifferent == pentagon);
}

TEST(FigureArrayTest, TotalAreaAndCopy) {
    FigureArray array;

    {
        auto trapezoid = std::make_unique<Trapezoid>();
        std::stringstream data("0 0 4 0 3 2 1 2");
        data >> *trapezoid;
        array.PushBack(std::move(trapezoid));
    }
    {
        auto rhombus = std::make_unique<Rhombus>();
        std::stringstream data("0 0 2 1 4 0 2 -1");
        data >> *rhombus;
        array.PushBack(std::move(rhombus));
    }

    EXPECT_NEAR(array.TotalArea(), 10.0, kTolerance);

    FigureArray copy(array);
    array.Remove(0);

    EXPECT_EQ(copy.Size(), 2U);
    EXPECT_NEAR(copy.TotalArea(), 10.0, kTolerance);
    EXPECT_EQ(array.Size(), 1U);
}
