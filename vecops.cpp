
#include "vecops.h"

vecops operator-(const vecops& a, const vecops& b) {
    return vecops(a[0]-b[0], a[1]-b[1], a[2]-b[2]);
}

vecops operator+(const vecops& a, const vecops& b) {
    return vecops(a[0]+b[0], a[1]+b[1], a[2]+b[2]);
}

double operator*(const vecops& a, const vecops& b) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

vecops operator*(const vecops& a, double k) {
    return vecops(a[0]*k, a[1]*k, a[2]*k);
}

vecops operator*(double k, const vecops& a) {
    return vecops(a[0]*k, a[1]*k, a[2]*k);
}

vecops cross(const vecops& a, const vecops& b) {
    return vecops(a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]);
}
