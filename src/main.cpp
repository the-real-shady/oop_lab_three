#include "figure_array.hpp"
#include "pentagon.hpp"
#include "rhombus.hpp"
#include "trapezoid.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <stdexcept>

namespace {

std::string ToLower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return value;
}

std::unique_ptr<Figure> MakeFigure(const std::string& type) {
    const std::string typeLower = ToLower(type);
    if (typeLower == "trapezoid" || typeLower == "t") {
        return std::make_unique<Trapezoid>();
    }
    if (typeLower == "rhombus" || typeLower == "r") {
        return std::make_unique<Rhombus>();
    }
    if (typeLower == "pentagon" || typeLower == "p") {
        return std::make_unique<Pentagon>();
    }
    throw std::invalid_argument("Unknown figure type: " + type);
}

void PrintMenu() {
    std::cout << "Commands:\n"
              << "  add <type>    - add figure of type trapezoid|rhombus|pentagon\n"
              << "  print         - print figures with centers and areas\n"
              << "  total         - print total area of figures\n"
              << "  remove <idx>  - remove figure by index\n"
              << "  clear         - remove all figures\n"
              << "  exit          - terminate program\n"
              << std::endl;
}

}  // namespace

int main() {
    FigureArray figures;
    PrintMenu();
    std::string command;
    while (true) {
        std::cout << "> ";
        if (!(std::cin >> command)) {
            break;
        }
        const std::string commandLower = ToLower(command);
        try {
            if (commandLower == "add") {
                std::string type;
                if (!(std::cin >> type)) {
                    std::cerr << "Expected figure type after 'add'\n";
                    continue;
                }
                auto figure = MakeFigure(type);
                std::cout << "Enter vertices (x y) pairs:\n";
                figure->Read(std::cin);
                figures.PushBack(std::move(figure));
                std::cout << "Figure added. Total figures: " << figures.Size() << '\n';
            } else if (commandLower == "print") {
                if (figures.Size() == 0) {
                    std::cout << "No figures stored.\n";
                } else {
                    figures.PrintAll(std::cout);
                }
            } else if (commandLower == "total") {
                std::cout << "Total area: " << figures.TotalArea() << '\n';
            } else if (commandLower == "remove") {
                std::size_t index{};
                if (!(std::cin >> index)) {
                    std::cerr << "Expected index after 'remove'\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                figures.Remove(index);
                std::cout << "Removed figure at index " << index << ". Remaining: " << figures.Size() << '\n';
            } else if (commandLower == "clear") {
                while (figures.Size() > 0) {
                    figures.Remove(figures.Size() - 1);
                }
                std::cout << "All figures removed.\n";
            } else if (commandLower == "exit" || commandLower == "quit") {
                break;
            } else {
                std::cerr << "Unknown command: " << command << '\n';
                PrintMenu();
            }
        } catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << '\n';
        }
    }
    return 0;
}
