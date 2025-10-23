#pragma once

#include "geometry.hpp"

#include <iosfwd>
#include <memory>
#include <vector>

class Figure {
public:
    virtual ~Figure() = default;

    virtual Point Center() const = 0;
    virtual double Area() const = 0;
    virtual std::unique_ptr<Figure> Clone() const = 0;
    virtual bool Equals(const Figure& other) const = 0;

    virtual void Print(std::ostream& os) const = 0;
    virtual void Read(std::istream& is) = 0;

    explicit operator double() const { return Area(); }

    bool operator==(const Figure& other) const { return Equals(other); }
    bool operator!=(const Figure& other) const { return !(*this == other); }
};

std::ostream& operator<<(std::ostream& os, const Figure& figure);
std::istream& operator>>(std::istream& is, Figure& figure);
