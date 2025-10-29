#include "geometry.hpp"

#include <cmath>
#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>

std::istream& operator>>(std::istream& is, Point& point) {
    return is >> point.x >> point.y;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << '(' << point.x << ", " << point.y << ')';
    return os;
}

bool operator==(const Point& lhs, const Point& rhs) {
    constexpr double kEpsilon = 1e-9;
    return std::fabs(lhs.x - rhs.x) < kEpsilon && std::fabs(lhs.y - rhs.y) < kEpsilon;
}

static void EnsureValidPolygon(std::size_t count) {
    if (count < 3) {
        throw std::invalid_argument("Polygon must contain at least three vertices");
    }
}

double PolygonSignedAreaRaw(const Point* points, std::size_t count) {
    EnsureValidPolygon(count);
    double area = 0.0;
    for (std::size_t i = 0; i < count; ++i) {
        const Point& p1 = points[i];
        const Point& p2 = points[(i + 1) % count];
        area += (p1.x * p2.y) - (p2.x * p1.y);
    }
    return area / 2.0;
}

double PolygonAreaRaw(const Point* points, std::size_t count) {
    return std::fabs(PolygonSignedAreaRaw(points, count));
}

Point PolygonCentroidRaw(const Point* points, std::size_t count) {
    EnsureValidPolygon(count);
    const double signedArea = PolygonSignedAreaRaw(points, count);
    if (std::fabs(signedArea) <= std::numeric_limits<double>::epsilon()) {
        throw std::invalid_argument("Polygon area is zero; centroid is undefined");
    }
    double cx = 0.0;
    double cy = 0.0;
    for (std::size_t i = 0; i < count; ++i) {
        const Point& p1 = points[i];
        const Point& p2 = points[(i + 1) % count];
        const double cross = (p1.x * p2.y) - (p2.x * p1.y);
        cx += (p1.x + p2.x) * cross;
        cy += (p1.y + p2.y) * cross;
    }
    const double factor = 1.0 / (6.0 * signedArea);
    cx *= factor;
    cy *= factor;
    return {cx, cy};
}
