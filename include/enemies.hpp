#ifndef ENEMIES_H
#define ENEMIES_H

#include "raylib.h"
#include "map.hpp"
#include <vector>
#include "Vec2.hpp"
using namespace std;

class GameManager;
class baseEnemy {
protected:
    Texture2D texture;
    GameManager* game;
    float moveSpeed;

public:
    int pathPos;
    int damage;
    float size;
    Vec2 position;
    int hp;
    int value;
    bool reachedEnd;
    bool isDelay;
    Sound sound;
    baseEnemy(GameManager* game);
    void update();
    virtual void draw_enemy();
    virtual ~baseEnemy();
};

class basicEnemy : public baseEnemy {
public:
    basicEnemy(GameManager* game);
};

class eliteEnemy : public baseEnemy {
public:
    eliteEnemy(GameManager* game);
};

class tankEnemy : public baseEnemy {
public:
    tankEnemy(GameManager* game);
};

class brute : public baseEnemy {
public:
    brute(GameManager* game);
};

class veteran : public baseEnemy {
public:
    veteran(GameManager* game);
};

class dasher : public baseEnemy {
public:
    dasher(GameManager* game);
};

class superTank : public baseEnemy {
public:
    superTank(GameManager* game);
};

class delay : public baseEnemy {
public:
    delay(GameManager* game);
};

#endif