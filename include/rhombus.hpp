#pragma once

#include "figure.hpp"

#include <array>

class Rhombus : public Figure {
public:
    Rhombus();
    explicit Rhombus(const std::array<Point, 4>& vertices);
    Rhombus(const Rhombus& other) = default;
    Rhombus(Rhombus&& other) noexcept = default;
    Rhombus& operator=(const Rhombus& other) = default;
    Rhombus& operator=(Rhombus&& other) noexcept = default;
    ~Rhombus() override = default;

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
