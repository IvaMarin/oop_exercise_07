/* 
 *  Мариничев И. А.
 *  М8О-208Б-19
 *  github.com/IvaMarin/oop_exercise_07
 *  Вариант 13:
 *  Фигура:    
 *  - ромб
 *  - пятиугольник 
 *  - шестиугольник
 */


#include <iostream>
#include <memory>
#include <vector>

#include "document.hpp"

void Menu() {
    std::cout << "1. Create new document" << std::endl;
    std::cout << "2. Save document" << std::endl;
    std::cout << "3. Open document" << std::endl;
    std::cout << "4. Add figure" << std::endl;
    std::cout << "5. Remove figure" << std::endl;
    std::cout << "6. Print figures" << std::endl;
    std::cout << "7. Undo" << std::endl;
    std::cout << "8. Help" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << std::endl;
}

int main() {
    Menu();
    std::shared_ptr<document> doc;
    int cmd;

    std::cout << "Select option: ";
    while (true) {
        std::cin >> cmd;
        if (cmd == 1) {
            std::string name;
            std::cout << "Enter document's name:" << std::endl;
            std::cin >> name;
            doc = std::make_shared<document>(name);
            std::cout << "Created new document" << std::endl;
        } else if (cmd == 2) {
            if (!doc) {
                std::cout << "Open document first" << std::endl;
            } else {
                try {
                    doc->Save();
                    std::cout << "Successfully saved" << std::endl;
                }
                catch (std::exception &ex) {
                    std::cout << ex.what() << std::endl;
                }
            }
        } else if (cmd == 3) {
            std::string file_name;
            std::cout << "Enter file's name: " << std::endl;
            std::cin >> file_name;
            std::ifstream in;
            in.open(file_name, std::ios::in | std::ios::binary);
            if (!in.is_open()) {
                std::cout << "No such file" << std::endl;
            } else {
                doc = std::make_shared<document>(file_name);
                try {
                    doc->Open(in);
                    std::cout << "File was successfully loaded" << std::endl;
                }
                catch (std::exception &ex) {
                    std::cout << ex.what() << std::endl;
                }
                in.close();
            }
        } else if (cmd == 4) {
            if (!doc) {
                std::cout << "Open document first" << std::endl;
            } else {
                std::cout << "Enter figure id (1 - rhombus, 2 - pentagon, 3 - hexagon)" << std::endl;
                int type;
                std::cin >> type;
                if (type == 1) {
                    std::cout << "Enter coords of the center and lengths of diagonals" << std::endl;
                } else if (type == 2) {
                    std::cout << "Enter coords of the center and length of radius" << std::endl;
                } else if (type == 3) {
                    std::cout << "Enter coords of the center and length of side" << std::endl;
                }
                std::shared_ptr<Figure> fig = factory::Create((FigureType) type);
                doc->Add(fig);
                std::cout << "Figure was successfully added" << std::endl;
            }
        } else if (cmd == 5) {
            if (!doc) {
                std::cout << "Open document first" << std::endl;
            } else {
                int id;
                std::cout << "Enter id of the figure" << std::endl;
                std::cin >> id;
                try {
                    doc->Remove(id);
                    std::cout << "Figure was successfully removed" << std::endl;
                }
                catch (std::exception &ex) {
                    std::cout << ex.what() << std::endl;
                }
            }
        } else if (cmd == 6) {
            if (!doc) {
                std::cout << "Open document first" << std::endl;
            } else {
                doc->Print();
            }
        } else if (cmd == 7) {
            if (!doc) {
                std::cout << "Open document first" << std::endl;
            } else {
                try {
                    doc->Undo();
                    std::cout << "Done" << std::endl;
                }
                catch (std::exception &ex) {
                    std::cout << ex.what() << std::endl;
                }
            }
        } else if (cmd == 8) {
            Menu();
        } else if (cmd == 0) {
            break;
        } else {
            std::cout << "Wrong cmd" << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Select option: "; // Repeat input
    }
}