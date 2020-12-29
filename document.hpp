#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <stack>
#include <fstream>

#include "factory.hpp"

class document {
private:

    struct memento {
        std::vector<std::shared_ptr<Figure>> state;

        memento() = default;

        memento(std::vector<std::shared_ptr<Figure>> &other) : state(other) {}
    };

    struct originator {
        std::stack<memento> mementos;

        void create_memento(std::vector<std::shared_ptr<Figure>> &state) {
            mementos.emplace(state);
        }

        std::vector<std::shared_ptr<Figure>> restore() {
            if (!mementos.empty()) {
                std::vector<std::shared_ptr<Figure>> res = mementos.top().state;
                mementos.pop();
                return res;
            }
            throw std::logic_error("Can't undo");
        }
    };

    std::string name;
    std::vector<std::shared_ptr<Figure>> buffer;
    originator origin;

public:
    document(std::string &name_) : name(name_) {}

    void Add(const std::shared_ptr<Figure> &figure) {
        origin.create_memento(buffer);
        buffer.push_back(figure);
    }

    void Remove(int id) {
        if (id >= 0 && id < buffer.size()) {
            origin.create_memento(buffer);
            buffer.erase(buffer.begin() + id);
        } else {
            throw std::logic_error("Invalid position");
        }
    }

    void Undo() {
        buffer = origin.restore();
    }

    void Print() {
        for (auto &f : buffer) {
            f->Print();
            std::cout << std::endl;
            std::cout << "2. Area of figure: " << f->Area() << std::endl;
            auto center = f->GetCenter();
            std::cout << "3. Center: (" << center.first << "; " << center.second << ")" << std::endl;
        }
    }

    void Save() {
        std::ofstream out;
        out.open(name, std::ios::out | std::ios::binary | std::ios::trunc);
        if (!out.is_open()) {
            throw std::logic_error("Can't open file");
        } else {
            int size = buffer.size();
            out.write((char *) &size, sizeof(int));
            for (auto &f : buffer) {
                f->WriteToFile(out);
            }
            out.close();
        }
    }

    void Open(std::ifstream &in) {
        int size;
        in.read((char *) &size, sizeof(int));
        for (int i = 0; i < size; ++i) {
            int type;
            in.read((char *) &type, sizeof(int));
            buffer.push_back(factory::ReadFromFile((FigureType) type, in));
        }
    }

};

#endif //DOCUMENT_HPP