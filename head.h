//
// Created by Гошик on 01.06.2022.
//

#ifndef INC_5_8_HEAD_H
#define INC_5_8_HEAD_H

#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
#include <vector>
#include <omp.h>
#include <string>
#include <map>

#include "vecops.h"
#include "box.h"
#include "light.h"

struct Parametrs {
    vecops cam;
    vecops normal;
    vecops up;
    double screen;
    double limit;
    double alpha;
    size_t width;
    size_t height;
    Light light;
};

#define PI 3.14159265358979323846


bool scene_intersect(const vecops&, const vecops&, const std::vector<box*>&, vecops&, vecops&, vecops&, double);
vecops cast_ray(const vecops&, const vecops&, const std::vector<box*>&, const Light&, double);
void render(const std::vector<box*>&, Parametrs&);


bool GetParametrs(const std::string&, Parametrs&);
bool GetFigures(const std::string&, std::vector<box*>&);

#endif //INC_5_8_HEAD_H
