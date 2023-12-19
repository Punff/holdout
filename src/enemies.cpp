#include "enemies.hpp"
#include "raylib.h"

baseEnemy::baseEnemy(){

}

baseEnemy::~baseEnemy(){

}

basicEnemy::basicEnemy(Map* map){
    this->map = map;

    this->damage = 1;
    this->hp = 10;
    this->moveSpeed = 500;
    this->pathPos = 0;
    
    this->position.x = map->get_tile_xPos(map->enemyPath[pathPos].x) + map->get_tile_size() / 2;
    this->position.y = map->get_tile_yPos(map->enemyPath[pathPos].y) + map->get_tile_size() / 2;
}

void basicEnemy::update(){
    if(pathPos >= map->enemyPath.size()){
        delete this;
        return;
    }

    Vec2 wishPos;
    wishPos.x = map->get_tile_xPos(map->enemyPath[pathPos + 1].x) + map->get_tile_size() / 2;
    wishPos.y = map->get_tile_yPos(map->enemyPath[pathPos + 1].y) + map->get_tile_size() / 2;

    Vec2 dir = wishPos - position;
    if(dir.lenght() <= (dir.normalized() * moveSpeed * GetFrameTime()).lenght()){
        position = wishPos;
        pathPos++;
        return;
    }

    position = position + (dir.normalized() * moveSpeed) * GetFrameTime();
}

void basicEnemy::draw_enemy(){
    DrawCircle(position.x, position.y, map->get_tile_size() * 0.8f / 2, RED);
}