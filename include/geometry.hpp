#pragma once

#include <iosfwd>
#include <vector>

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

double PolygonSignedArea(const std::vector<Point>& points);
double PolygonArea(const std::vector<Point>& points);
Point PolygonCentroid(const std::vector<Point>& points);
