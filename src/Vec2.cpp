#include "Vec2.hpp"
#include <cmath>

Vec2::Vec2(float x, float y){
    this->x = x;
    this->y = y;
}

float Vec2::lenght(){
    return sqrt(pow(x, 2) + pow(y, 2));
}

void Vec2::normalize(){
    x /= lenght();
    y /= lenght();
}