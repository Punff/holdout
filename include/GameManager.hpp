#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "map.hpp"
#include "towers.hpp"
#include "gameUI.hpp"
#include "enemies.hpp"
#include <raylib.h>
#include <vector>
#include "Vec2.hpp"
#include "waves.hpp"

class GameManager {
private:
    int screenWidth;
    int screenHeight;

public:
    int playerHP;
    int money;
    Map* map;
    WaveManager* waveManager;
    vector<baseTower*> towers;
    bool isPlacingTower;
    vector<baseProjectile*> projectiles;
    GameManager();
    ~GameManager();
    void gameloop();
    void load_map(string mapName);
    void take_damage(int damage);
};

#endif