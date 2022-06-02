#include "head.h"

bool GetParametrs(const std::string& FileName, Parametrs& param) {
    std::ifstream inp(FileName);

    if(!inp){
        std::cout << "Error! Cannot open file: " << FileName << "\n";
        return 0;
    }

    while(!inp.eof()){
        std::string I; inp >> I;

        if(I == "cam") {
            double x, y, z;
            inp >> x >> y >> z;
            param.cam = vecops(x, y, z);
        }
        else if(I == "width") {
            inp >> param.width;
        }
        else if(I == "height") {
            inp >> param.height;
        }
        else if(I == "light") {
            double x, y, z;
            inp >> x >> y >> z;
            param.light = vecops(x, y ,z);
        }
        else if(I == "normal") {
            double x, y, z;
            inp >> x >> y >> z;
            param.normal = vecops(x, y ,z);
        }
        else if(I == "up") {
            double x, y, z;
            inp >> x >> y >> z;
            param.up = vecops(x, y ,z);
        }
        else if(I == "screen") {
            inp >> param.screen;
        }
        else if(I == "limit") {
            inp >> param.limit;
        }
        else if(I == "alpha") {
            inp >> param.alpha;
        }
        else{
            std::cout << "Error! Unknown parametr: " << I << "\n";
            inp.close();
            return 0;
        }
    }

    inp.close();

    return 1;
}

bool GetFigures(const std::string& FileName, std::vector<box*>& objects) {
    std::ifstream inp(FileName);
    if(!inp){
        std::cout << "Error! Cannot open file: " << FileName << "\n";
        return 0;
    }

    while(!inp.eof()) {
        std::string I; inp >> I;

        if(I == "box") {
            double x1, y1, z1, x2, y2, z2;
            inp >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            objects.push_back(new Box(vecops(x1, y1, z1), vecops(x2, y2, z2)));
            double r, g, b;
            inp >> r >> g >> b;
            objects[objects.size()-1]->UpdateColour(vecops(r, g, b));
        }
        else {
            inp.close();
            std::cout << "Error! Unknown type: " << I << "\n";
            return 0;
        }
    }
    inp.close();

    return 1;
}