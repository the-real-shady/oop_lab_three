#include "pentagon.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

Pentagon::Pentagon() = default;

Pentagon::Pentagon(const std::array<Point, 5>& vertices) : vertices_(vertices) {}

Point Pentagon::Center() const {
    std::vector<Point> points(vertices_.begin(), vertices_.end());
    return PolygonCentroid(points);
}

double Pentagon::Area() const {
    std::vector<Point> points(vertices_.begin(), vertices_.end());
    return PolygonArea(points);
}

std::unique_ptr<Figure> Pentagon::Clone() const {
    return std::make_unique<Pentagon>(*this);
}

bool Pentagon::Equals(const Figure& other) const {
    const auto* otherPentagon = dynamic_cast<const Pentagon*>(&other);
    if (!otherPentagon) {
        return false;
    }
    return vertices_ == otherPentagon->vertices_;
}

void Pentagon::Print(std::ostream& os) const {
    os << "Pentagon:";
    for (const auto& vertex : vertices_) {
        os << ' ' << vertex;
    }
    os << " | center=" << Center() << " | area=" << Area();
}

void Pentagon::Read(std::istream& is) {
    for (auto& vertex : vertices_) {
        if (!(is >> vertex)) {
            throw std::runtime_error("Failed to read pentagon vertex");
        }
    }
}
