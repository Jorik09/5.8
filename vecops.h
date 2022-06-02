//
// Created by Гошик on 01.06.2022.
//

#ifndef INC_5_8_VECOPS_H
#define INC_5_8_VECOPS_H

#include <iostream>
#include <cassert>
#include <cmath>

class vecops {
private:
    double _vec[3] = {0.0, 0.0, 0.0};
public:
    vecops() = default;
    vecops(double x, double y, double z) {
        _vec[0] = x;
        _vec[1] = y;
        _vec[2] = z;
    }
    vecops(const vecops& a) {
        _vec[0] = a._vec[0];
        _vec[1] = a._vec[1];
        _vec[2] = a._vec[2];
    }

    vecops& operator=(const vecops& n){
        if(this == &n) return *this;
        _vec[0] = n._vec[0];
        _vec[1] = n._vec[1];
        _vec[2] = n._vec[2];
        return *this;
    }

    double norm() const{
        return sqrt(_vec[0]*_vec[0]+_vec[1]*_vec[1]+_vec[2]*_vec[2]);
    }
    vecops& normalize() {
        double k = 1/norm();
        _vec[0] *= k;
        _vec[1] *= k;
        _vec[2] *= k;
        return *this;
    }

    double& operator[](const size_t i) {
        assert(i < 3);
        return _vec[i];
    }
    const double& operator[](const size_t i) const {
        assert(i < 3);
        return _vec[i];
    }

    void print() const{
        std::cout << "(" << _vec[0] << "; " << _vec[1] << "; " << _vec[2] << ")";
    }

};

vecops operator-(const vecops&, const vecops&);
vecops operator+(const vecops&, const vecops&);
double operator*(const vecops&, const vecops&);
vecops operator*(const vecops&, double);
vecops operator*(double, const vecops&);
vecops cross(const vecops&, const vecops&);

#endif //INC_5_8_VECOPS_H
