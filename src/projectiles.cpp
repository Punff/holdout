#include "projectiles.hpp"
#include "towers.hpp"
#include "enemies.hpp"
#include "raylib.h"

baseProjectile::baseProjectile(baseTower *shooter, const baseEnemy &target) {
    this->pos = shooter->position;
    this->targetPos = target.position;
    this->damage = shooter->damage;
    this->speed = shooter->attackSpeed;
}

basicProjectile::basicProjectile(basicTower *shooter, const baseEnemy &target) : baseProjectile(shooter, target) {}

void basicProjectile::draw_projectile() {
    DrawCircleV({ pos.x, pos.y }, 5, RED);
}


