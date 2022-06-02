//
// Created by Гошик on 01.06.2022.
//
#include <limits>
#include "box.h"
vecops box::colour() const {
    return _colour;
};
void box::UpdateColour(const vecops& colour) {
    _colour = colour*(1/255.0);
}


double Box::ray_intersect(const vecops& orig, const vecops& dir) const {
    double t_near = std::numeric_limits<double>::min(),
            t_far  = std::numeric_limits<double>::max();
    double t1, t2;

    for(int i = 0; i < 3; ++i) {
        double d = dir[i];
        if(d < 0.0) d *= -1;
        if(d >= std::numeric_limits<double>::epsilon()) {
            t1 = (_A[i] - orig[i]) / dir[i];
            t2 = (_B[i] - orig[i]) / dir[i];
            if(t1 > t2) std::swap(t1, t2);


            if(t1 > t_near) t_near = t1;
            if(t2 < t_far) t_far = t2;

            if(t_near > t_far) return -1;
            if(t_far < 0.0) return -1;
        }
        else {
            if(orig[i] < _A[i] || orig[i] > _B[i] ) return -1;
        }
    }

    if(t_near <= t_far && t_far >=0) return t_near;
    else return -1;
}

vecops Box::center() const {
    return vecops( (_A[0]+_B[0])/2, (_A[1]+_B[1])/2, (_A[2]+_B[2])/2);
}