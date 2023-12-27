#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"
#include "map.hpp"
#include <vector>
#include "Vec2.hpp"
using namespace std;

class baseEnemy {
    protected:
    Map* map;
    int hp;
    float moveSpeed;
    int damage;
    Vec2 position;
    int pathPos;
    bool reachedEnd;

    public:
    baseEnemy(Map* map);
    virtual void update() = 0;
    virtual void draw_enemy() = 0;
    virtual ~baseEnemy();
};

class basicEnemy : public baseEnemy {
    public:
    basicEnemy(Map* map);
    void update();
    void draw_enemy();
};

#endif