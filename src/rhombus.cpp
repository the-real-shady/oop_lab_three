#include "rhombus.hpp"

#include <iostream>
#include <stdexcept>

Rhombus::Rhombus() = default;

Rhombus::Rhombus(const std::array<Point, 4>& vertices) : vertices_(vertices) {}

Point Rhombus::Center() const {
    return PolygonCentroid(vertices_);
}

double Rhombus::Area() const {
    return PolygonArea(vertices_);
}

std::unique_ptr<Figure> Rhombus::Clone() const {
    return std::make_unique<Rhombus>(*this);
}

bool Rhombus::Equals(const Figure& other) const {
    const auto* otherRhombus = dynamic_cast<const Rhombus*>(&other);
    if (!otherRhombus) {
        return false;
    }
    return vertices_ == otherRhombus->vertices_;
}

void Rhombus::Print(std::ostream& os) const {
    os << "Rhombus:";
    for (const auto& vertex : vertices_) {
        os << ' ' << vertex;
    }
    os << " | center=" << Center() << " | area=" << Area();
}

void Rhombus::Read(std::istream& is) {
    for (auto& vertex : vertices_) {
        if (!(is >> vertex)) {
            throw std::runtime_error("Failed to read rhombus vertex");
        }
    }
}
