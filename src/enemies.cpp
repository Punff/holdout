#include "enemies.hpp"
#include "raylib.h"

baseEnemy::baseEnemy(Map* map){
    this->map = map;
    this->size = map->get_tile_size();
    this->pathPos = 0;
    this->position.x = map->get_tile_xPos(map->enemyPath[pathPos].x) + size / 2;
    this->position.y = map->get_tile_yPos(map->enemyPath[pathPos].y) + size / 2;
    this->reachedEnd = false;
}

baseEnemy::~baseEnemy(){}

void baseEnemy::update(){
    if(pathPos >= map->enemyPath.size() - 1){
        reachedEnd = true;
        return;
    }

    Vec2 wishPos;
    wishPos.x = map->get_tile_xPos(map->enemyPath[pathPos + 1].x) + size / 2;
    wishPos.y = map->get_tile_yPos(map->enemyPath[pathPos + 1].y) + size / 2;

    Vec2 dir = wishPos - position;
    if(dir.length() <= (dir.normalized() * moveSpeed * size * GetFrameTime()).length()){
        position = wishPos;
        pathPos++;
        return;
    }

    position = position + (dir.normalized() * moveSpeed * size) * GetFrameTime();
}

basicEnemy::basicEnemy(Map* map) : baseEnemy(map){
    this->damage = 1;
    this->hp = 10;
    this->moveSpeed = 1;
}

void basicEnemy::draw_enemy(){
    DrawCircle(position.x, position.y, size * 0.8f / 2, RED);
}

eliteEnemy::eliteEnemy(Map* map) : baseEnemy(map){
    this->damage = 1;
    this->hp = 15;
    this->moveSpeed = 1.5;
}

void eliteEnemy::draw_enemy(){
    DrawCircle(position.x, position.y, size * 0.8f / 2, PINK);
}