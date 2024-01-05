#include "towers.hpp"
#include "GameManager.hpp"

baseTower::baseTower(GameManager* game, float x, float y) {
    this->game = game;
    this->size = game->map->get_tile_size();
    this->position = { x, y };
    this->rotation = 0;
    this->toggleRange = false;
}

void baseTower::update_tower() {
    baseEnemy* target = get_enemy_in_range();

    if(target != NULL){
        rotation = Vector2Angle({0, -1}, target->position - position) * 180 / PI;
    }

    cooldown -= GetFrameTime();
    if(cooldown <= 0){
        if(target != NULL){
            shoot_projectile();
            cooldown = attackDelay;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), {position.x - size / 2, position.y - size / 2, size, size}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        toggleRange = !toggleRange;
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
    if (toggleRange)
        DrawCircleLines(position.x, position.y, range * size, ORANGE);
}

basicTower::basicTower(GameManager* game, float x, float y) : baseTower(game, x, y) {
    texture = LoadTexture("assets/textures/tower.png");
    range = 2.0f;
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
    DrawTexturePro(texture, {0, 0, 16, 16}, {position.x, position.y, size, size}, {size / 2, size / 2}, rotation,
                   WHITE);
    draw_range();
}

void basicTower::shoot_projectile() {
    
}
