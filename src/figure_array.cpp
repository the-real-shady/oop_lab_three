#include "figure_array.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>

FigureArray::FigureArray(const FigureArray& other) {
    figures_.reserve(other.figures_.size());
    for (const auto& figure : other.figures_) {
        if (figure) {
            figures_.push_back(figure->Clone());
        }
    }
}

FigureArray& FigureArray::operator=(const FigureArray& other) {
    if (this == &other) {
        return *this;
    }
    FigureArray temp(other);
    figures_.swap(temp.figures_);
    return *this;
}

void FigureArray::PushBack(std::unique_ptr<Figure> figure) {
    if (!figure) {
        throw std::invalid_argument("Cannot push back null figure");
    }
    figures_.push_back(std::move(figure));
}

void FigureArray::Remove(std::size_t index) {
    if (index >= figures_.size()) {
        throw std::out_of_range("Figure index is out of range");
    }
    figures_.erase(figures_.begin() + static_cast<std::ptrdiff_t>(index));
}

std::size_t FigureArray::Size() const noexcept {
    return figures_.size();
}

const Figure& FigureArray::At(std::size_t index) const {
    if (index >= figures_.size()) {
        throw std::out_of_range("Figure index is out of range");
    }
    return *figures_.at(index);
}

Figure& FigureArray::At(std::size_t index) {
    if (index >= figures_.size()) {
        throw std::out_of_range("Figure index is out of range");
    }
    return *figures_.at(index);
}

double FigureArray::TotalArea() const {
    double total = 0.0;
    for (const auto& figure : figures_) {
        if (figure) {
            total += static_cast<double>(*figure);
        }
    }
    return total;
}

void FigureArray::PrintAll(std::ostream& os) const {
    for (std::size_t i = 0; i < figures_.size(); ++i) {
        os << '[' << i << "] " << *figures_[i] << '\n';
    }
}
