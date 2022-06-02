//
// Created by Гошик on 01.06.2022.
//

#ifndef INC_5_8_LIGHT_H
#define INC_5_8_LIGHT_H
#include <iostream>
#include "vecops.h"


struct Light {
    vecops _position;
    double _intensity;

    Light(): _position(), _intensity(0.0) {};
    Light(const vecops& position): _position(position), _intensity(0.0) {};
    Light(const vecops& position, double intensity): _position(position), _intensity(intensity) {};
    Light(const Light& light): _position(light._position), _intensity(light._intensity) {};

    Light& operator=(const Light& light){
        if(this == &light) return *this;
        _position = light._position;
        _intensity = light._intensity;
        return *this;
    }
};

#endif //INC_5_8_LIGHT_H
