#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "UI.hpp"
#include <iostream>
#include "map.hpp"
#include "towers.hpp"
#include "enemies.hpp"
#include "Vec2.hpp"
#include "waves.hpp"
#include <vector>
#include <raylib.h>

using namespace std;

class UI; // Forward declaration

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
    string towerType;
    vector<baseProjectile*> projectiles;

    enum class GameMode {
        MainMenu,
        InGame,
        Exit
    };

    GameMode currentMode;

    GameManager();
    ~GameManager();
    void gameloop();
    void load_map(string mapName);
    void take_damage(int damage);
    void drawInGame(UI* gameUI);
    void updateInGame();
    void drawMainMenu();
    void updateMainMenu();
};

#endif
