#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <cmath>

class Figure {
public:
    Figure() = default;

    Figure(std::pair<double, double> &center_) : center(center_) {}

    virtual double Area() = 0;

    virtual void Print() = 0;

    virtual void WriteToFile(std::ofstream &out) = 0;

    std::pair<double, double> GetCenter() {
        return center;
    }

protected:
    std::pair<double, double> center;
};

#endif // FIGURE_HPP