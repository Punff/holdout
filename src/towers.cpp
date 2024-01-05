#include "towers.hpp"
#include "GameManager.hpp"
#include "projectiles.hpp"

baseTower::baseTower(GameManager* game, float x, float y) {
    this->game = game;
    this->size = game->map->get_tile_size();
    position = { x, y };
    this->rotation = 0;
    this->level = 1;
}

void baseTower::update_tower() {
    baseEnemy* target = get_enemy_in_range();

    if(target != NULL){
        rotation = Vector2Angle({0, -1}, target->position - position) * 180 / PI;
    }

    cooldown -= GetFrameTime();
    if(cooldown <= 0){
        if(target != NULL){
            shoot_projectile(target->position);
            cooldown = attackDelay;
        }
    }

}

baseEnemy* baseTower::get_enemy_in_range(){
    for(baseEnemy* el : game->waveManager->activeEnemies){
        if(CheckCollisionPointCircle(el->position, position, range * size)){
            return el;
        }
    }
    return NULL;
}

void baseTower::draw_range() {
    DrawCircleLines(position.x, position.y, range * size, ORANGE);
}

basicTower::basicTower(GameManager* game, float x, float y) : baseTower(game, x, y) {
    texture = LoadTexture("assets/textures/tower.png");
    range = 2.5f;
    cost = 15;
    attackDelay = 1.5f;
    cooldown = 0.0f;
    damage = 5;
}

basicTower::~basicTower(){
    UnloadTexture(texture);
}

void basicTower::draw_tower() {
    DrawTexturePro(texture, {16, 0, 16, 16}, {position.x, position.y, size, size}, {size / 2, size / 2}, 0, WHITE);
    DrawTexturePro(texture, {0, 0, 16, 16}, {position.x, position.y, size, size}, {size / 2, size / 2}, rotation, WHITE);

    if (IsKeyDown(KEY_R))
        draw_range();
}

void basicTower::shoot_projectile(Vec2 targetPos) {
    game->projectiles.push_back(new basicProjectile(game, position, targetPos));
}
