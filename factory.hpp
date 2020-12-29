#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "rhombus.hpp"
#include "pentagon.hpp"
#include "hexagon.hpp"

enum class FigureType {
    RHOMBUS = 1,
    PENTAGON = 2,
    HEXAGON = 3
};

struct factory {
    static std::shared_ptr<Figure> Create(FigureType t) { //Initializing figures from input
        switch (t) {
            case FigureType::RHOMBUS: {
                std::pair<double, double> center;
                double d1, d2;
                std::cin >> center.first >> center.second >> d1 >> d2;
                return std::make_shared<Rhombus>(center, d1, d2);
            }
            case FigureType::PENTAGON: {
                std::pair<double, double> center;
                double r;
                std::cin >> center.first >> center.second >> r;
                return std::make_shared<Pentagon>(center, r);
            }
            case FigureType::HEXAGON: {
                std::pair<double, double> center;
                double r;
                std::cin >> center.first >> center.second >> r;
                return std::make_shared<Hexagon>(center, r);
            }
            default:
                throw std::logic_error("Wrong figure id");
        }
    }

    static std::shared_ptr<Figure> ReadFromFile(FigureType t, std::ifstream &in) { //Initializing figures from file
        switch (t) {
            case FigureType::RHOMBUS: {
                std::pair<double, double> center;
                double d1, d2;
                in.read((char *) &center.first, sizeof(double));
                in.read((char *) &center.second, sizeof(double));
                in.read((char *) &d1, sizeof(double));
                in.read((char *) &d2, sizeof(double));
                return std::make_shared<Rhombus>(center, d1, d2);
            }
            case FigureType::PENTAGON: {
                std::pair<double, double> center;
                double r;
                in.read((char *) &center.first, sizeof(double));
                in.read((char *) &center.second, sizeof(double));
                in.read((char *) &r, sizeof(double));
                return std::make_shared<Pentagon>(center, r);
            }
            case FigureType::HEXAGON: {
                std::pair<double, double> center;
                double r;
                in.read((char *) &center.first, sizeof(double));
                in.read((char *) &center.second, sizeof(double));
                in.read((char *) &r, sizeof(double));
                return std::make_shared<Hexagon>(center, r);
            }
            default:
                throw std::logic_error("Wrong figure id");
        }
    }
};

#endif //FACTORY_HPP