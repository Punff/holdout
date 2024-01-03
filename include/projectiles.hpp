#ifndef PROJECTILES_H
#define PROJECTILES_H

#include "Vec2.hpp"
#include "towers.hpp"
#include "enemies.hpp"

class baseTower;

class baseProjectile {
protected:
    Vec2 pos;
    Vec2 targetPos;
    int damage;
    float speed;

public:
    baseProjectile(baseTower* shooter, const baseEnemy& target);
    virtual void update_projectile() = 0;
    virtual void draw_projectile() = 0;
};

class basicProjectile : public baseProjectile {
public:
    basicProjectile(basicTower* shooter, const baseEnemy& target);

    void update_projectile() override;
    void draw_projectile() override;
};

#endif
