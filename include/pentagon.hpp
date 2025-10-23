#pragma once

#include "figure.hpp"

#include <array>

class Pentagon : public Figure {
public:
    Pentagon();
    explicit Pentagon(const std::array<Point, 5>& vertices);
    Pentagon(const Pentagon& other) = default;
    Pentagon(Pentagon&& other) noexcept = default;
    Pentagon& operator=(const Pentagon& other) = default;
    Pentagon& operator=(Pentagon&& other) noexcept = default;
    ~Pentagon() override = default;

    Point Center() const override;
    double Area() const override;
    std::unique_ptr<Figure> Clone() const override;
    bool Equals(const Figure& other) const override;
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;

    const std::array<Point, 5>& Vertices() const { return vertices_; }

private:
    std::array<Point, 5> vertices_;
};
