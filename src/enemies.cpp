#include "enemies.hpp"
#include "raylib.h"
#include "GameManager.hpp"

baseEnemy::baseEnemy(GameManager* game){
    this->game = game;
    this->sound = game->assets->load_sound("enemySound.wav");
    this->size = game->map->get_tile_size();
    this->pathPos = 0;
    this->position.x = game->map->get_tile_xPos(game->map->enemyPath[pathPos].x) + size / 2;
    this->position.y = game->map->get_tile_yPos(game->map->enemyPath[pathPos].y) + size / 2;
    this->reachedEnd = false;
}

baseEnemy::~baseEnemy(){

}

void baseEnemy::update(){
    if(pathPos >= game->map->enemyPath.size() - 1){
        reachedEnd = true;
        return;
    }

    Vec2 wishPos;
    wishPos.x = game->map->get_tile_xPos(game->map->enemyPath[pathPos + 1].x) + size / 2;
    wishPos.y = game->map->get_tile_yPos(game->map->enemyPath[pathPos + 1].y) + size / 2;

    Vec2 dir = wishPos - position;
    if(dir.length() <= (dir.normalized() * moveSpeed * size * GetFrameTime()).length()){
        position = wishPos;
        pathPos++;
        return;
    }

    position = position + (dir.normalized() * moveSpeed * size) * GetFrameTime();
}

void baseEnemy::draw_enemy(){
    DrawTexturePro(texture, {0, 0, 32, 32}, {position.x, position.y, size, size}, {size / 2, size / 2}, 0, WHITE);
}

basicEnemy::basicEnemy(GameManager* game) : baseEnemy(game){
    texture = game->assets->load_texture("text-enemy-basic.png");
    damage = 1;
    value = 5;
    hp = 10;
    moveSpeed = 1;
}

eliteEnemy::eliteEnemy(GameManager* game) : baseEnemy(game){
    texture = game->assets->load_texture("text-enemy-elite.png");
    damage = 1;
    value = 10;
    hp = 15;
    moveSpeed = 1.5;
}

tankEnemy::tankEnemy(GameManager* game) : baseEnemy(game){
    texture = game->assets->load_texture("text-enemy-tank.png");
    damage = 35;
    value = 30;
    hp = 100;
    moveSpeed = 0.8;
}
