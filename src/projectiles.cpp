#include "projectiles.hpp"
#include "towers.hpp"
#include "enemies.hpp"
#include "raylib.h"

baseProjectile::baseProjectile(baseTower *shooter, baseEnemy &target, int size) {
    this->position = { shooter->position.x + size / 2, shooter->position.y + size / 2 };
    this->target = &target;
    this->damage = shooter->damage;
    this->speed = 500.0f;
    this->shouldDelete = false;
}

basicProjectile::basicProjectile(baseTower *shooter, baseEnemy &target, int size) : baseProjectile(shooter, target, size) {}

void basicProjectile::update_projectile(baseTower* shooter) {
    baseProjectile::update_projectile(shooter);
}

void basicProjectile::draw_projectile() {
    baseProjectile::draw_projectile();
}

void baseProjectile::draw_projectile() {
    DrawCircleV({ position.x, position.y }, 10, RED);
}

void baseProjectile::update_projectile(baseTower* shooter) {
    Vec2 dir = (target->position - position).normalized();

    position = position + dir * speed * GetFrameTime();

    if (CheckCollisionPointCircle({ position.x, position.y }, { target->position.x, target->position.y }, target->size / 2)) {
        // Handle damage
        shooter->busy = false;
        shouldDelete = true;
    }
}


