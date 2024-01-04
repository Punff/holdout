#ifndef PROJECTILES_H
#define PROJECTILES_H

#include "Vec2.hpp"
#include "towers.hpp"
#include "enemies.hpp"
#include <vector>
#include <algorithm>

using namespace std;

class baseTower;

class baseProjectile {
protected:
    Vec2 position;
    int damage;
    float speed;


public:
    baseEnemy* target;
    baseProjectile(baseTower* shooter, baseEnemy& target, int size);
    virtual void update_projectile(baseTower* shooter);
    virtual void draw_projectile();

    bool shouldDelete;
};

class basicProjectile : public baseProjectile {
public:
    basicProjectile(baseTower* shooter, baseEnemy& target, int size);

    void update_projectile(baseTower* shooter) override;
    void draw_projectile() override;
};

#endif
