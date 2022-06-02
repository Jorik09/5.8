#include <iostream>
#include "head.h"

int main() {
    Parametrs param;
    std::vector<box*> objects;

    std::string fp = "par.txt";
    std::string fo = "obj.txt";


    //std::cout << "Enter file with parametrs: ";
    //std::cin >> file;

    bool res1 = GetParametrs(fp, param);
    if(!res1) {
        return -1;
    }

    //std::cout << "Enter file with objects: ";
    //std::cin >> file;

    bool res2 = GetFigures(fo, objects);
    if(!res2) {
        return -1;
    }

    render(objects, param);

    return 0;
}
