#ifndef TOWERS_H
#define TOWERS_H

#include "Vec2.hpp"
#include "projectiles.hpp"
#include <vector>
#include "raylib.h"

using namespace std;

class baseEnemy;  // Forward declaration
class baseProjectile;  // Forward declaration

class baseTower {
public:
    baseProjectile* projectile;
    Vec2 position;
    int damage;
    float cooldown;
    float attackSpeed;
    float range;
    int cost;
    bool busy;

    baseTower(float x, float y);
    virtual void update_tower(vector<baseEnemy*>& activeEnemies, int size);
    virtual void draw_tower(int size);
    virtual void draw_range(int size);
    virtual bool is_enemy_in_range(const baseEnemy* target, int size);
    virtual void shoot_projectile(int size);
};

class basicTower : public baseTower {
public:
    basicTower(float x, float y);
    void draw_tower(int size) override;
    void draw_range(int size) override;
    bool is_enemy_in_range(const baseEnemy* target, int size) override;
    void shoot_projectile(int size) override;
};

#endif
