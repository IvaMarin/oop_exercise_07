#ifndef PENTAGON_HPP
#define PENTAGON_HPP

#include "figure.hpp"

class Pentagon : public Figure {
public:
    Pentagon() = default;

    Pentagon(std::pair<double, double> &center, double rad) : Figure(center), radius(rad) {}

    double Area() override {
        double pi = acos(-1);
        double side = radius * cos(13 * pi / 10) - radius * cos(17 * pi / 10);
        return sqrt(25 + 10 * sqrt(5)) * pow(side, 2) * 0.25;
    }

    void Print() override {
        std::cout << *this;
    }

    void WriteToFile(std::ofstream &out) override {
        int id = 2;
        out.write((char *) &id, sizeof(int));
        out.write((char *) &center.first, sizeof(double));
        out.write((char *) &center.second, sizeof(double));
        out.write((char *) &radius, sizeof(double));
    }

    friend std::ostream &operator<<(std::ostream &out, Pentagon &p);

private:
    double radius = 0;
};

std::ostream &operator<<(std::ostream &out, Pentagon &p) {
    std::cout << "\nPentagon:" << std::endl;
    std::cout << "1. Coordinates: ";
    double pi = acos(-1);
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * pi * i / 5;
        std::cout.precision(2);
        std::cout << "(" << p.center.first + p.radius * cos(angle + pi / 10) << "; "
                  << p.center.second + p.radius * sin(angle + pi / 10) << ")";
        if (i != 4) {
            std::cout << ", ";
        }
    }
    return out;
}


#endif //PENTAGON_HPP