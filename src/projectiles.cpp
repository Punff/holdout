#include "projectiles.hpp"
#include "towers.hpp"
#include "enemies.hpp"
#include "raylib.h"
#include "GameManager.hpp"

baseProjectile::baseProjectile(GameManager* game, Vec2 position, Vec2 targetPos) {
    this->game = game;
    this->position = position;
    size = game->map->get_tile_size() * 0.2f;
    dir = targetPos - position;
    shouldDelete = false;
    lifetime = 10;
}

baseProjectile::~baseProjectile(){ }

void baseProjectile::update() {
    lifetime -= GetFrameTime();
    if(lifetime <= 0){
        shouldDelete = true;
    }

    position = position + (dir.normalized() * speed * size) * GetFrameTime();

    for(baseEnemy* el : game->waveManager->activeEnemies){
        if(CheckCollisionPointCircle(position, el->position, game->map->get_tile_size() * 0.7f)){
            el->hp -= damage;
            shouldDelete = true;
        }
    }
}

basicProjectile::basicProjectile(GameManager* game, Vec2 position, Vec2 targetPos) : baseProjectile(game, position, targetPos){
    texture = LoadTexture("assets/textures/pellet.png");
    damage = 3;
    speed = 20;
}

basicProjectile::~basicProjectile(){
    UnloadTexture(texture);
}

void basicProjectile::draw_projectile() {
    DrawTexturePro(texture, {0, 0, 13, 13}, {position.x, position.y, size, size}, {size / 2, size / 2}, 0, WHITE);
}