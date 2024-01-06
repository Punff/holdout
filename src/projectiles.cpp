#include "projectiles.hpp"
#include "towers.hpp"
#include "enemies.hpp"
#include "raylib.h"
#include "GameManager.hpp"
#define ENEMY_SIZE 0.45f
baseProjectile::baseProjectile(GameManager* game, Vec2 position, Vec2 targetPos, int damage) {
    this->game = game;
    this->position = position;
    size = game->map->get_tile_size() * 0.2f;
    dir = targetPos - position;
    this->damage = damage;
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
        if(CheckCollisionPointCircle(position, el->position, game->map->get_tile_size() * ENEMY_SIZE)){
            el->hp -= damage;
            shouldDelete = true;
        }
    }
}

basicProjectile::basicProjectile(GameManager* game, Vec2 position, Vec2 targetPos, int damage) : baseProjectile(game, position, targetPos, damage){
    texture = LoadTexture("assets/textures/pellet.png");
    speed = 20;
}

basicProjectile::~basicProjectile(){
    UnloadTexture(texture);
}

void basicProjectile::draw_projectile() {
    DrawTexturePro(texture, {0, 0, 13, 13}, {position.x, position.y, size, size}, {size / 2, size / 2}, 0, WHITE);
}

flameRing::flameRing(GameManager* game, Vec2 position, Vec2 targetPos, int damage, float range) : baseProjectile(game, position, targetPos, damage){
    texture = LoadTexture("assets/textures/flame-ring.png");
    speed = 0;
    lifetime = 0.6f;
    size = game->map->get_tile_size() * range;
    rotation = 0;
    didDamage = false;
}

flameRing::~flameRing(){
    UnloadTexture(texture);
}

void flameRing::update(){
    lifetime -= GetFrameTime();
    if(lifetime <= 0){
        shouldDelete = true;
    }
    
    rotation += 100 * GetFrameTime();
    
    if(!didDamage){
        for(baseEnemy* el : game->waveManager->activeEnemies){
            if(CheckCollisionCircles(position, size, el->position, game->map->get_tile_size() * ENEMY_SIZE)){
                el->hp -= damage;
            }
        }
        didDamage = true;
    }
}

void flameRing::draw_projectile(){
    DrawTexturePro(texture, {0, 0, 23, 23}, {position.x, position.y, size * 2, size * 2}, {size, size}, rotation, WHITE);
}