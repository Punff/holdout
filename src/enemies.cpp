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
    this->moveSpeed = 50;
    this->pathPos = 0;
    
    this->position.x = map->get_tile_xPos(map->enemyPath[pathPos].x) + map->get_tile_size() / 2;
    this->position.y = map->get_tile_yPos(map->enemyPath[pathPos].y) + map->get_tile_size() / 2;
}

void basicEnemy::update(){
    if(pathPos >= map->enemyPath.size()){
        delete this;
        return;
    }

    Vector2 wishPos;
    wishPos.x = map->get_tile_xPos(map->enemyPath[pathPos + 1].x);
    wishPos.y = map->get_tile_yPos(map->enemyPath[pathPos + 1].y);

    Vector2 dir;
    dir.x = wishPos.x - position.x;
    dir.y = wishPos.y - position.y;

    dir.x /= dir.x;
}

void basicEnemy::draw_enemy(){
    DrawCircle(position.x, position.y, map->get_tile_size() * 0.8f / 2, RED);
}