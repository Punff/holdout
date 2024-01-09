#include "towers.hpp"
#include "GameManager.hpp"
#include "projectiles.hpp"

baseTower::baseTower(GameManager* game, float x, float y) {
    this->game = game;
    this->size = game->map->get_tile_size();
    this->position = { x, y };
    this->rotation = 0;
    this->level = 1;
    this->toggleRange = true;
}

baseTower::~baseTower(){}

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

int basicTower::price = 30;

basicTower::basicTower(GameManager* game, float x, float y) : baseTower(game, x, y) {
    texture = game->assets->load_texture("tower.png");
    range = 2.9f;
    attackDelay = 1.5f;
    cooldown = 0;
    damage = 5;
}

void basicTower::draw_tower() {
    DrawTexturePro(texture, {16, 0, 16, 16}, {position.x, position.y, size, size}, {size / 2, size / 2}, 0, WHITE);
    DrawTexturePro(texture, {0, 0, 16, 16}, {position.x, position.y, size, size}, {size / 2, size / 2}, rotation,
                   WHITE);
    draw_range();
}

void basicTower::shoot_projectile(Vec2 targetPos) {
    game->projectiles.push_back(new basicProjectile(game, position, targetPos, damage));
}

int flamethrower::price = 70;

flamethrower::flamethrower(GameManager* game, float x, float y) : baseTower(game, x, y) {
    texture = game->assets->load_texture("text-tower-flamethrower.png");
    range = 1.4f;
    attackDelay = 2.0f;
    cooldown = 0;
    damage = 4;
}

void flamethrower::draw_tower(){
    DrawTexturePro(texture, {0, 0, 18, 18}, {position.x, position.y, size, size}, {size / 2, size / 2}, 0, WHITE);
    draw_range();
}

void flamethrower::shoot_projectile(Vec2 targetPos){
    game->projectiles.push_back(new flameRing(game, position, targetPos, damage, range));
}

int minigun::price = 250;

minigun::minigun(GameManager* game, float x, float y) : baseTower(game, x, y) {
    texture = game->assets->load_texture("text-tower-minigun.png");
    range = 0.5f;
    attackDelay = 0.3f;
    cooldown = attackDelay;
    damage = 5;
    targetPos = position + Vec2(0, -1);
}

void minigun::update_tower(){
    if(toggleRange && IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !CheckCollisionPointRec(GetMousePosition(), {position.x - size / 2, position.y - size / 2, size, size})){
        rotation = Vector2Angle({0, -1}, Vector2Subtract(GetMousePosition(), position)) * 180 / PI;
        targetPos = GetMousePosition();
        toggleRange = false;
    }

    if(game->waveManager->active)
        cooldown -= GetFrameTime();
    if(cooldown <= 0){
        shoot_projectile(targetPos);
        cooldown = attackDelay;
    }

    if (CheckCollisionPointRec(GetMousePosition(), {position.x - size / 2, position.y - size / 2, size, size}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        toggleRange = !toggleRange;
    }
}

void minigun::draw_tower(){
    DrawTexturePro(texture, {16, 0, 16, 16}, {position.x, position.y, size, size}, {size / 2, size / 2}, 0, WHITE);
    DrawTexturePro(texture, {0, 0, 16, 16}, {position.x, position.y, size, size}, {size / 2, size / 2}, rotation,
                   WHITE);
    draw_range();
}

void minigun::shoot_projectile(Vec2 targetPos){
    game->projectiles.push_back(new basicProjectile(game, position, targetPos, damage));
}

int cannon::price = 150;

cannon::cannon(GameManager* game, float x, float y) : baseTower(game, x, y){
    texture = game->assets->load_texture("text-tower-artillery.png");
    range = 3.2f;
    attackDelay = 2.5f;
    cooldown = 0;
    damage = 5;
}

void cannon::draw_tower(){
    DrawTexturePro(texture, {0, 0, 16, 16}, {position.x, position.y, size, size}, {size / 2, size / 2}, rotation,
                   WHITE);
    draw_range();
}

void cannon::shoot_projectile(Vec2 targetPos){
    game->projectiles.push_back(new bomb(game, position, targetPos, damage));
}
