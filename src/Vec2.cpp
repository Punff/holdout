#include "Vec2.hpp"
#include <cmath>

Vec2::Vec2(){
    this->x = 0;
    this->y = 0;
}

Vec2::Vec2(float x, float y){
    this->x = x;
    this->y = y;
}

float Vec2::length(){
    return sqrt(pow(x, 2) + pow(y, 2));
}

Vec2 Vec2::normalized(){
    float len = this->length();
    Vec2 v(x / len, y / len);
    return v;
}

Vec2 Vec2::operator+(const Vec2& other){
    Vec2 v(this->x + other.x, this->y + other.y);
    return v;
}

Vec2 Vec2::operator-(const Vec2& other){
    Vec2 v(this->x - other.x, this->y - other.y);
    return v;
}

Vec2::operator Vector2() const {
    Vector2 v;
    v.x = this->x;
    v.y = this->y;
    return v;
}

bool Vec2::operator==(const Vec2& other){
    if(this->x == other.x && this->y == other.y){
        return true;
    }
    else{
        return false;
    }
}

bool Vec2::operator!=(const Vec2& other){
    return !(*this == other);
}

Vec2 Vec2::operator*(float s){
    this->x *= s;
    this->y *= s;
    return *this;
}