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
    lifetime = 5;
}

baseProjectile::~baseProjectile(){ }

void baseProjectile::update() {
    lifetime -= GetFrameTime();
    if(lifetime <= 0){
        shouldDelete = true;
    }

    position = position + (dir.normalized() * speed * size) * GetFrameTime();

    for(baseEnemy* el : game->waveManager->activeEnemies){
        if(CheckCollisionPointCircle(position, el->position, game->map->get_tile_size() * ENEMY_SIZE)) {
            PlaySound(el->sound);
            el->hp -= damage;
            shouldDelete = true;
            return;
        }
    }
}

basicProjectile::basicProjectile(GameManager* game, Vec2 position, Vec2 targetPos, int damage) : baseProjectile(game, position, targetPos, damage){
    texture = game->assets->load_texture("pellet.png");
    speed = 30;
}

void basicProjectile::draw_projectile() {
    DrawTexturePro(texture, {0, 0, 13, 13}, {position.x, position.y, size, size}, {size / 2, size / 2}, 0, WHITE);
}

flameRing::flameRing(GameManager* game, Vec2 position, Vec2 targetPos, int damage, float range) : baseProjectile(game, position, targetPos, damage){
    texture = game->assets->load_texture("flame-ring.png");
    speed = 0;
    lifetime = 0.6f;
    size = game->map->get_tile_size() * range;
    rotation = 0;
    didDamage = false;
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


bomb::bomb(GameManager* game, Vec2 position, Vec2 targetPos, int damage) : baseProjectile(game, position, targetPos, damage){
    texture = game->assets->load_texture("bomb.png");
    speed = 25;
}

void bomb::update(){
    lifetime -= GetFrameTime();
    if(lifetime <= 0){
        shouldDelete = true;
    }

    position = position + (dir.normalized() * speed * size) * GetFrameTime();

    for(baseEnemy* el : game->waveManager->activeEnemies){
        if(CheckCollisionPointCircle(position, el->position, game->map->get_tile_size() * ENEMY_SIZE)){
            el->hp -= damage;
            shouldDelete = true;
            game->projectiles.push_back(new explosion(game, position, {0, 0}, damage));
            return;
        }
    }
}

void bomb::draw_projectile(){ // drawn 2x bigger
    DrawTexturePro(texture, {0, 0, 14, 14}, {position.x, position.y, size * 2, size * 2}, {size, size}, 0, WHITE);
}

explosion::explosion(GameManager* game, Vec2 position, Vec2 targetPos, int damage) : baseProjectile(game, position, targetPos, damage) {
    texture = game->assets->load_texture("explosion.png");
    size = game->map->get_tile_size() * 1.20;
    speed = 0;
    lifetime = 0.5;
    maxLifetime = lifetime;
    didDamage = false;
}

void explosion::update(){
    lifetime -= GetFrameTime();
    if(lifetime <= 0){
        shouldDelete = true;
    }
    
    if(!didDamage){
        for(baseEnemy* el : game->waveManager->activeEnemies){
            if(CheckCollisionCircles(position, size, el->position, game->map->get_tile_size() * ENEMY_SIZE)){
                el->hp -= damage;
            }
        }
        didDamage = true;
    }
}

void explosion::draw_projectile(){
    if(lifetime / maxLifetime < 0.25){
        DrawTexturePro(texture, {96, 0, 32, 32}, {position.x, position.y, size * 2, size * 2}, {size, size}, 0, WHITE);
    } else if(lifetime / maxLifetime < 0.5){
        DrawTexturePro(texture, {64, 0, 32, 32}, {position.x, position.y, size * 2, size * 2}, {size, size}, 0, WHITE);
    } else if(lifetime / maxLifetime < 0.75){
        DrawTexturePro(texture, {32, 0, 32, 32}, {position.x, position.y, size * 2, size * 2}, {size, size}, 0, WHITE);
    } else {
        DrawTexturePro(texture, {0, 0, 32, 32}, {position.x, position.y, size * 2, size * 2}, {size, size}, 0, WHITE);
    }
}

arrow::arrow(GameManager* game, Vec2 position, Vec2 targetPos, int damage) : baseProjectile(game, position, targetPos, damage){
    texture = game->assets->load_texture("arrow.png");
    speed = 45;
    pierces = 3;
}

void arrow::update(){
    lifetime -= GetFrameTime();
    if(lifetime <= 0){
        shouldDelete = true;
    }

    position = position + (dir.normalized() * speed * size) * GetFrameTime();

    for(baseEnemy* el : game->waveManager->activeEnemies){
        if(CheckCollisionPointCircle(position, el->position, game->map->get_tile_size() * ENEMY_SIZE)){
            if(enemy_was_hit(el)){
                continue;
            }
            el->hp -= damage;
            hits.push_back(el);
            pierces--;
            if(pierces <= 0){
                shouldDelete = true;
            }
            return;
        }
    }
}

bool arrow::enemy_was_hit(baseEnemy* enemy){
    for(baseEnemy* el : hits){
        if(el == enemy){
            return true;
        }
    }
    return false;
}

void arrow::draw_projectile(){
    float sizeMod = size * 3;
    DrawTexturePro(texture, {0, 0, 13, 13}, {position.x, position.y, sizeMod, sizeMod}, {sizeMod / 2, sizeMod / 2}, Vector2Angle({0, -1}, dir) * 180 / PI, WHITE);
}

railShot::railShot(GameManager* game, Vec2 position, Vec2 targetPos, int damage) : baseProjectile(game, position, targetPos, damage){
    texture = game->assets->load_texture("rail-shot.png");
    this->targetPos = targetPos;
    lifetime = RAIL_SHOT_LIFETIME;
}

void railShot::update(){
    lifetime -= GetFrameTime();
    if(lifetime <= 0){
        shouldDelete = true;
    }
}

void railShot::draw_projectile(){
    float xPos = (targetPos.x - position.x) / 2;
    float yPos = (targetPos.y - position.y) / 2;
    float lenght = (targetPos - position).length();

    // Main beam
    if(lifetime > RAIL_SHOT_LIFETIME * 2 / 3)
    DrawTexturePro(texture, {5, 0, 6, 16}, {position.x + xPos, position.y + yPos, size, lenght}, {size / 2, lenght / 2}, Vector2Angle({0, -1}, dir) * 180 / PI, WHITE);

    // Explosion
    float explSize = size * 5;
    if(lifetime < RAIL_SHOT_LIFETIME / 3){
        DrawTexturePro(texture, {48, 0, 16, 16}, {targetPos.x, targetPos.y, explSize, explSize}, {explSize / 2, explSize / 2}, Vector2Angle({0, -1}, dir) * 180 / PI, WHITE);
    } else if(lifetime < RAIL_SHOT_LIFETIME * 2 / 3){
        DrawTexturePro(texture, {32, 0, 16, 16}, {targetPos.x, targetPos.y, explSize, explSize}, {explSize / 2, explSize / 2}, Vector2Angle({0, -1}, dir) * 180 / PI, WHITE);
    } else {
        DrawTexturePro(texture, {16, 0, 16, 16}, {targetPos.x, targetPos.y, explSize, explSize}, {explSize / 2, explSize / 2}, Vector2Angle({0, -1}, dir) * 180 / PI, WHITE);        
    }
}