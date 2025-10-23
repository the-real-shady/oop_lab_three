#pragma once

#include "figure.hpp"

#include <array>
#include <string>

class Trapezoid : public Figure {
public:
    Trapezoid();
    explicit Trapezoid(const std::array<Point, 4>& vertices);
    Trapezoid(const Trapezoid& other) = default;
    Trapezoid(Trapezoid&& other) noexcept = default;
    Trapezoid& operator=(const Trapezoid& other) = default;
    Trapezoid& operator=(Trapezoid&& other) noexcept = default;
    ~Trapezoid() override = default;

    Point Center() const override;
    double Area() const override;
    std::unique_ptr<Figure> Clone() const override;
    bool Equals(const Figure& other) const override;
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;

    const std::array<Point, 4>& Vertices() const { return vertices_; }

private:
    std::array<Point, 4> vertices_;
};
