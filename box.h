//
// Created by Гошик on 01.06.2022.
//

#ifndef INC_5_8_BOX_H
#define INC_5_8_BOX_H

#include <iostream>
#include "vecops.h"

class box {
protected:
    vecops _colour;
public:
    box(): _colour() {};
    box(const vecops& color): _colour(color) {};

    virtual double ray_intersect(const vecops&, const vecops&) const = 0;

    virtual vecops center() const = 0;

    vecops colour() const;
    void UpdateColour(const vecops&);

    virtual ~box(){};
};


class Box : public box {
private:
    vecops _A = {0.0, 0.0, 0.0};
    vecops _B = {1.0, 1.0, 1.0};
public:
    Box() = default;
    Box(const vecops& A, const vecops& B, const vecops& colour): box(colour), _A(A), _B(B) {};
    Box(const vecops& A, const vecops& B): box(), _A(A), _B(B) {};

    double ray_intersect(const vecops&, const vecops&) const override;

    vecops center() const override;
};



#endif //INC_5_8_BOX_H
