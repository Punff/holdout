#include "enemies.hpp"
#include "raylib.h"
#include "GameManager.hpp"

baseEnemy::baseEnemy(GameManager* game){
    this->game = game;
    sound = game->assets->load_sound("enemySound.wav");
    size = game->map->get_tile_size();
    pathPos = 0;
    position.x = game->map->get_tile_xPos(game->map->enemyPath[pathPos].x) + size / 2;
    position.y = game->map->get_tile_yPos(game->map->enemyPath[pathPos].y) + size / 2;
    reachedEnd = false;
    isDelay = false;
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
    damage = 5;
    value = 2;
    hp = 10;
    moveSpeed = 1;
}

eliteEnemy::eliteEnemy(GameManager* game) : baseEnemy(game){
    texture = game->assets->load_texture("text-enemy-elite.png");
    damage = 10;
    value = 4;
    hp = 20;
    moveSpeed = 1.3;
}

veteran::veteran(GameManager* game) : baseEnemy(game){
    texture = game->assets->load_texture("text-enemy-veteran.png");
    damage = 15;
    value = 6;
    hp = 40;
    moveSpeed = 1.1;
}

brute::brute(GameManager* game) : baseEnemy(game){
    texture = game->assets->load_texture("text-enemy-brute.png");
    damage = 24;
    value = 15;
    hp = 100;
    moveSpeed = 0.8;
}

dasher::dasher(GameManager* game) : baseEnemy(game){
    texture = game->assets->load_texture("text-enemy-dasher.png");
    damage = 15;
    value = 8;
    hp = 100;
    moveSpeed = 1.6;
}

tankEnemy::tankEnemy(GameManager* game) : baseEnemy(game){
    texture = game->assets->load_texture("text-enemy-tank.png");
    damage = 60;
    value = 20;
    hp = 300;
    moveSpeed = 0.8;
}

superTank::superTank(GameManager* game) : baseEnemy(game){
    texture = game->assets->load_texture("text-enemy-super-tank.png");
    damage = 150;
    value = 80;
    hp = 1200;
    moveSpeed = 0.7;
}

delay::delay(GameManager* game) : baseEnemy(game){
    isDelay = true;
}