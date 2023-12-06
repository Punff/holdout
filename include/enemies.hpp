#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"
#include <vector>
using namespace std;

class baseEnemy {
    protected:
    int hp;
    int moveSpeed;
    int damage;
    Rectangle hitbox;
    vector<Vector2> path;

    public:
    baseEnemy();
    virtual void draw_enemy() = 0;
    virtual ~baseEnemy();
};

class basicEnemy : public baseEnemy {
    public:
    basicEnemy(int xPos, int yPos, vector<Vector2> path);
    void draw_enemy();
};

#endif