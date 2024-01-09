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
    Texture2D texture;
    GameManager* game;
    Vec2 position;
    float rotation;
    float size;
    int damage;
    float cooldown;
    float attackDelay;
    float range;
    bool toggleRange;
    int level;

    baseTower(GameManager* game, float x, float y);
    virtual ~baseTower();
    virtual void update_tower();
    void draw_range();
    baseEnemy* get_enemy_in_range();
    virtual void draw_tower() = 0;
    virtual void shoot_projectile(Vec2 targetPos) = 0;
};

class basicTower : public baseTower {
public:
    static int price;
    basicTower(GameManager* game, float x, float y);
    void draw_tower() override;
    void shoot_projectile(Vec2 targetPos) override;
};

class flamethrower : public baseTower {
public:
    static int price;
    flamethrower(GameManager* game, float x, float y);
    void draw_tower() override;
    void shoot_projectile(Vec2 targetPos) override;
};

class minigun : public baseTower {
private:
    Vec2 targetPos;
public:
    static int price;
    minigun(GameManager* game, float x, float y);
    void update_tower() override;
    void draw_tower() override;
    void shoot_projectile(Vec2 targetPos) override;
};

class cannon : public baseTower {
public:
    static int price;
    cannon(GameManager* game, float x, float y);
    void draw_tower() override;
    void shoot_projectile(Vec2 targetPos) override;
};

class crossbow : public baseTower {
public:
    static int price;
    crossbow(GameManager* game, float x, float y);
    void draw_tower() override;
    void shoot_projectile(Vec2 targetPos) override;
};

class railgun : public baseTower {
public:
    static int price;
    railgun(GameManager* game, float x, float y);
    void update_tower() override;
    void draw_tower() override;
    void shoot_projectile(Vec2 targetPos) override;
};

#endif
