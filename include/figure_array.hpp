#pragma once

#include "figure.hpp"

#include <cstddef>
#include <memory>
#include <vector>

class FigureArray {
public:
    FigureArray() = default;
    FigureArray(const FigureArray& other);
    FigureArray(FigureArray&& other) noexcept = default;
    FigureArray& operator=(const FigureArray& other);
    FigureArray& operator=(FigureArray&& other) noexcept = default;
    ~FigureArray() = default;

    void PushBack(std::unique_ptr<Figure> figure);
    void Remove(std::size_t index);
    [[nodiscard]] std::size_t Size() const noexcept;
    [[nodiscard]] const Figure& At(std::size_t index) const;
    [[nodiscard]] Figure& At(std::size_t index);
    [[nodiscard]] double TotalArea() const;
    void PrintAll(std::ostream& os) const;

    std::vector<std::unique_ptr<Figure>>::const_iterator begin() const { return figures_.begin(); }
    std::vector<std::unique_ptr<Figure>>::const_iterator end() const { return figures_.end(); }

private:
    std::vector<std::unique_ptr<Figure>> figures_;
};
