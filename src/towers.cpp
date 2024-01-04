#include "towers.hpp"

baseTower::baseTower(float x, float y) {
    position = { x, y };
}

void baseTower::update_tower(vector<baseEnemy*>& activeEnemies, int size) {
    this->draw_tower(size);

    if (cooldown > 0.0f)
        cooldown -= GetFrameTime();

    if (!this->busy && cooldown <= 0.0f) {
        for (auto& target : activeEnemies) {
            if (is_enemy_in_range(target, size)) {
                this->projectile = new baseProjectile(this, *target, size);
                this->busy = true;
                this->cooldown = attackSpeed;
                break;
            }
        }
    }

    if (this->projectile) {
        this->projectile->update_projectile(this);
        this->projectile->draw_projectile();

        if (this->projectile->shouldDelete) {
            delete this->projectile;
            this->projectile = nullptr;
            this->busy = false;
        }
    }

    if (IsKeyDown(KEY_R))
        this->draw_range(size);
}

void baseTower::shoot_projectile(int size) {
    if (!this->busy && this->projectile) {
        this->projectile->update_projectile(this);
        this->projectile->draw_projectile();

        if (this->projectile->shouldDelete) {
            delete this->projectile;
            this->projectile = nullptr;
            this->busy = false;
        }
    }
}



bool baseTower::is_enemy_in_range(const baseEnemy* target, int size) {
    Vec2 center = {position.x + size / 2, position.y + size / 2};
    if (CheckCollisionPointCircle(target->position, center, range)) {
        return true;
    }
    return false;
}

basicTower::basicTower(float x, float y) : baseTower(x, y) {
    range = 350.f;
    cost = 15;
    attackSpeed = 1.5f;
    cooldown = 0.0f;
}

void baseTower::draw_tower(int size) {
    DrawRectangle(position.x + 50, position.y + 50, size - 100, size - 100, BLUE);
    //DrawRectangle(position.x + 30, position.y + 30, size - 60, size - 60, RED);
}

void baseTower::draw_range(int size) {
    DrawCircleLines(position.x + size / 2, position.y + size / 2, this->range, ORANGE);
}

void basicTower::draw_tower(int size) {
    baseTower::draw_tower(size);
}

void basicTower::draw_range(int size) {
    baseTower::draw_range(size);
}

bool basicTower::is_enemy_in_range(const baseEnemy* target, int size) {
    return baseTower::is_enemy_in_range(target, size);
}

void basicTower::shoot_projectile(int size) {
    baseTower::shoot_projectile(size);
}
