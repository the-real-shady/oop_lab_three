#pragma once

#include <array>
#include <cstddef>
#include <iosfwd>

struct Point {
    double x{0.0};
    double y{0.0};
};

std::istream& operator>>(std::istream& is, Point& point);
std::ostream& operator<<(std::ostream& os, const Point& point);
bool operator==(const Point& lhs, const Point& rhs);
inline bool operator!=(const Point& lhs, const Point& rhs) {
    return !(lhs == rhs);
}

double PolygonSignedAreaRaw(const Point* points, std::size_t count);
double PolygonAreaRaw(const Point* points, std::size_t count);
Point PolygonCentroidRaw(const Point* points, std::size_t count);

template <std::size_t N>
double PolygonSignedArea(const std::array<Point, N>& points) {
    return PolygonSignedAreaRaw(points.data(), N);
}

template <std::size_t N>
double PolygonArea(const std::array<Point, N>& points) {
    return PolygonAreaRaw(points.data(), N);
}

template <std::size_t N>
Point PolygonCentroid(const std::array<Point, N>& points) {
    return PolygonCentroidRaw(points.data(), N);
}
