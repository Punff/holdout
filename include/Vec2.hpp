#ifndef VEC2_H
#define VEC2_H

#include "raylib.h"

struct Vec2 {
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);
    float lenght();
    Vec2 normalized();

    Vec2 operator+(const Vec2& other);
    Vec2 operator-(const Vec2& other);
    Vec2 operator*(float s);
    bool operator==(const Vec2& other);
    bool operator!=(const Vec2& other);
    operator Vector2() const;
};

#endif