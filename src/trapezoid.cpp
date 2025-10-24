#include "trapezoid.hpp"

#include <iostream>
#include <stdexcept>

Trapezoid::Trapezoid() = default;

Trapezoid::Trapezoid(const std::array<Point, 4>& vertices) : vertices_(vertices) {}

Point Trapezoid::Center() const {
    return PolygonCentroid(vertices_);
}

double Trapezoid::Area() const {
    return PolygonArea(vertices_);
}

std::unique_ptr<Figure> Trapezoid::Clone() const {
    return std::make_unique<Trapezoid>(*this);
}

bool Trapezoid::Equals(const Figure& other) const {
    const auto* otherTrapezoid = dynamic_cast<const Trapezoid*>(&other);
    if (!otherTrapezoid) {
        return false;
    }
    return vertices_ == otherTrapezoid->vertices_;
}

void Trapezoid::Print(std::ostream& os) const {
    os << "Trapezoid:";
    for (const auto& vertex : vertices_) {
        os << ' ' << vertex;
    }
    os << " | center=" << Center() << " | area=" << Area();
}

void Trapezoid::Read(std::istream& is) {
    for (auto& vertex : vertices_) {
        if (!(is >> vertex)) {
            throw std::runtime_error("Failed to read trapezoid vertex");
        }
    }
}
