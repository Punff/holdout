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
#include "AssetServer.hpp"

using namespace std;

class UI; // Forward declaration

class GameManager {
private:
    int screenWidth;
    int screenHeight;

public:
    int playerHP;
    int money;
    bool paused;
    Map* map;
    WaveManager* waveManager;
    AssetServer* assets;
    vector<baseTower*> towers;
    bool isPlacingTower;
    string towerType;
    vector<baseProjectile*> projectiles;
    Sound mainMenu;
    Sound mainTheme;

    enum class GameMode {
        MainMenu,
        InGame,
        Exit,
        Victory,
        Defeat
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
    void drawVictory();
    void drawDefeat();
    void updateMainMenu();
};

#endif
