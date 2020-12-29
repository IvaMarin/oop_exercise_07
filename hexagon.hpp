#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "figure.hpp"

class Hexagon : public Figure {
public:
    Hexagon() = default;

    Hexagon(std::pair<double, double> &center, double rad) : Figure(center), radius(rad) {}

    double Area() override {
        return pow(radius, 2) * 3 * sqrt(3) * 0.5;
    }

    void Print() override {
        std::cout << *this;
    }

    void WriteToFile(std::ofstream &out) override {
        int id = 3;
        out.write((char *) &id, sizeof(int));
        out.write((char *) &center.first, sizeof(double));
        out.write((char *) &center.second, sizeof(double));
        out.write((char *) &radius, sizeof(double));
    }

    friend std::ostream &operator<<(std::ostream &out, Hexagon &h);

private:
    double radius = 0;
};

std::ostream &operator<<(std::ostream &out, Hexagon &h) {
    std::cout << "\nHexagon:" << std::endl;
    std::cout << "1. Coordinates: ";
    double pi = acos(-1);
    for (int i = 0; i < 6; ++i) {
        double angle = pi * i / 3;
        std::cout.precision(2);
        std::cout << "(" << h.center.first + h.radius * cos(angle) << "; "
                  << h.center.second + h.radius * sin(angle) << ")";
        if (i != 5) {
            std::cout << ", ";
        }
    }
    return out;
}


#endif //HEXAGON_HPP