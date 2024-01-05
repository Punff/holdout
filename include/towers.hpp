#ifndef TOWERS_H
#define TOWERS_H

#include "Vec2.hpp"
#include "projectiles.hpp"
#include "raylib.h"
#include "raymath.h"
#include "enemies.hpp"

class GameManager;

class baseTower {
public:
    GameManager* game;
    Vec2 position;
    float rotation;
    float size;
    int damage;
    float cooldown;
    float attackDelay;
    float range;
    int cost;

    baseTower(GameManager* game, float x, float y);
    void update_tower();
    void draw_range();
    baseEnemy* get_enemy_in_range();
    virtual void draw_tower() = 0;
    virtual void shoot_projectile() = 0;
};

class basicTower : public baseTower {
private:
    Texture2D texture;
public:
    basicTower(GameManager* game, float x, float y);
    void draw_tower() override;
    void shoot_projectile() override;
    ~basicTower();
};

#endif
