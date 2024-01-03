#ifndef TOWERS_H
#define TOWERS_H

#include "Vec2.hpp"
#include "projectiles.hpp"  // Include projectiles.hpp here

class baseEnemy;  // Forward declaration

class baseTower {
public:
    Vec2 position;
    int HP;
    int damage;
    float attackSpeed;
    float range;
    int cost;

    baseTower(float x, float y);
    virtual void draw_tower(int size) = 0;
    virtual void draw_range(float range, int size) = 0;
    virtual bool is_enemy_in_range(const baseEnemy& target) = 0;
    virtual void shoot_projectile(const baseEnemy& target) = 0;
};

class basicTower : public baseTower {
public:
    basicTower(float x, float y);
    void draw_tower(int size) override;
    void draw_range(float range, int size) override;
    bool is_enemy_in_range(const baseEnemy& target) override;
    void shoot_projectile(const baseEnemy& target) override;
};

#endif
