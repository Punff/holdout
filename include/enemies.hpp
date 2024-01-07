#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"
#include "map.hpp"
#include <vector>
#include "Vec2.hpp"
using namespace std;

class baseEnemy {
protected:
    Texture2D texture;
    Map* map;
    float moveSpeed;
    int pathPos;

public:
    int damage;
    float size;
    Vec2 position;
    int hp;
    int value;
    bool reachedEnd;
    baseEnemy(Map* map);
    void update();
    virtual void draw_enemy();
    virtual ~baseEnemy();
};

class basicEnemy : public baseEnemy {
public:
    basicEnemy(Map* map);
};

class eliteEnemy : public baseEnemy {
public:
    eliteEnemy(Map* map);
};

class tankEnemy : public baseEnemy {
public:
    tankEnemy(Map* map);
};

#endif