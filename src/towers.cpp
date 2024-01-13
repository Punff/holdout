#include "towers.hpp"
#include "GameManager.hpp"
#include "projectiles.hpp"

baseTower::baseTower(GameManager* game, float x, float y) {
    this->game = game;
    size = game->map->get_tile_size();
    position = { x, y };
    rotation = 0;
    level = 1;
    toggleRange = true;
    cooldown = 0;
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
    baseEnemy* target = NULL;
    int maxPos = -1;

    for(baseEnemy* el : game->waveManager->activeEnemies){
        if(CheckCollisionPointCircle(el->position, position, range * size) && el->pathPos > maxPos){
            target = el;
            maxPos = el->pathPos;
        }
    }

    return target;
}

void baseTower::draw_range() {
    if (toggleRange)
        DrawCircleLines(position.x, position.y, range * size, ORANGE);
}

int basicTower::price = 30;

basicTower::basicTower(GameManager* game, float x, float y) : baseTower(game, x, y) {
    texture = game->assets->load_texture("tower.png");
    sound = game->assets->load_sound("basicTowerShot.wav");
    range = 2.9f;
    attackDelay = 1.5f;
    damage = 8;
}

void basicTower::draw_tower() {
    DrawTexturePro(texture, {16, 0, 16, 16}, {position.x, position.y, size, size}, {size / 2, size / 2}, 0, WHITE);
    DrawTexturePro(texture, {0, 0, 16, 16}, {position.x, position.y, size, size}, {size / 2, size / 2}, rotation,
                   WHITE);
    draw_range();
}

void basicTower::shoot_projectile(Vec2 targetPos) {
    PlaySound(sound);
    game->projectiles.push_back(new basicProjectile(game, position, targetPos, damage));
}

int flamethrower::price = 90;

flamethrower::flamethrower(GameManager* game, float x, float y) : baseTower(game, x, y) {
    texture = game->assets->load_texture("text-tower-flamethrower.png");
    sound = game->assets->load_sound("flamethrowerShot.wav");
    range = 1.5f;
    attackDelay = 1.7f;
    damage = 6;
}

void flamethrower::draw_tower(){
    DrawTexturePro(texture, {0, 0, 18, 18}, {position.x, position.y, size, size}, {size / 2, size / 2}, 0, WHITE);
    draw_range();
}

void flamethrower::shoot_projectile(Vec2 targetPos){
    PlaySound(sound);
    game->projectiles.push_back(new flameRing(game, position, targetPos, damage, range));
}

int minigun::price = 300;

minigun::minigun(GameManager* game, float x, float y) : baseTower(game, x, y) {
    texture = game->assets->load_texture("text-tower-minigun.png");
    sound = game->assets->load_sound("basicTowerShot.wav");
    range = 0.5f;
    attackDelay = 0.3f;
    cooldown = attackDelay;
    damage = 9;
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

void minigun::shoot_projectile(Vec2 targetPos) {
    PlaySound(sound);
    game->projectiles.push_back(new basicProjectile(game, position, targetPos, damage));
}

int cannon::price = 250;

cannon::cannon(GameManager* game, float x, float y) : baseTower(game, x, y){
    texture = game->assets->load_texture("text-tower-artillery.png");
    sound = game->assets->load_sound("canonShot.wav");
    range = 3.2f;
    attackDelay = 2.3f;
    damage = 22;
}

void cannon::draw_tower(){
    DrawTexturePro(texture, {0, 0, 16, 16}, {position.x, position.y, size, size}, {size / 2, size / 2}, rotation,
                   WHITE);
    draw_range();
}

void cannon::shoot_projectile(Vec2 targetPos) {
    PlaySound(sound);
    game->projectiles.push_back(new bomb(game, position, targetPos, damage));
}

int crossbow::price = 80;

crossbow::crossbow(GameManager* game, float x, float y) : baseTower(game, x, y){
    texture = game->assets->load_texture("text-tower-crossbow.png");
    sound = game->assets->load_sound("crossbowShot.wav");
    range = 3.6f;
    attackDelay = 1.6;
    damage = 7;
}

void crossbow::draw_tower(){
    DrawTexturePro(texture, {15, 0, 15, 15}, {position.x, position.y, size, size}, {size / 2, size / 2}, 0, WHITE);
    DrawTexturePro(texture, {0, 0, 15, 15}, {position.x, position.y, size, size}, {size / 2, size / 2}, rotation,
                   WHITE);
    draw_range();
}

void crossbow::shoot_projectile(Vec2 targetPos) {
    PlaySound(sound);
    game->projectiles.push_back(new arrow(game, position, targetPos, damage));
}

int railgun::price = 600;

railgun::railgun(GameManager* game, float x, float y) : baseTower(game, x, y){
    texture = game->assets->load_texture("text-tower-railgun.png");
    sound = game->assets->load_sound("railgunShot.wav");
    range = 5.3;
    attackDelay = 8;
    damage = 400;
}

void railgun::update_tower(){
    baseEnemy* target = get_enemy_in_range();

    if(target != NULL && cooldown < attackDelay * 0.5){
        rotation = Vector2Angle({0, -1}, target->position - position) * 180 / PI;
    }

    cooldown -= GetFrameTime();
    if(cooldown <= 0){
        if(target != NULL){
            shoot_projectile(target->position);
            target->hp -= damage;
            cooldown = attackDelay;
            cooldown += (float)(GetRandomValue(0, 100) - 50) / 1500;
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), {position.x - size / 2, position.y - size / 2, size, size}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        toggleRange = !toggleRange;
    }
}

void railgun::draw_tower(){
    DrawTexturePro(texture, {64, 0, 32, 32}, {position.x, position.y, size, size}, {size / 2, size / 2}, 0, WHITE);

    if(cooldown < attackDelay - RAIL_SHOT_LIFETIME / 3){
        DrawTexturePro(texture, {0, 0, 32, 32}, {position.x, position.y, size, size}, {size / 2, size / 2}, rotation, WHITE);
    }
    else {
        DrawTexturePro(texture, {32, 0, 32, 32}, {position.x, position.y, size, size}, {size / 2, size / 2}, rotation, WHITE);
    }

    draw_range();
}

void railgun::shoot_projectile(Vec2 targetpos){
    PlaySound(sound);
    game->projectiles.push_back(new railShot(game, position, targetpos, damage));
}