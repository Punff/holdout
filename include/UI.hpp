#ifndef GAMEUI_H
#define GAMEUI_H

#include "raygui.h"
#include <iostream>
#include <vector>
#include "waves.hpp"
#include "towers.hpp"
#include <raylib.h>
#include "GameManager.hpp"
#include "map.hpp"

using namespace std;

class GameManager; // Forward declaration

class UI {
public:
    Vec2 leftCorner, rightCorner;
    int tileSize;
    int mapTiles;
    int height;
    int width;
    int padding;
    int lineHeight;
    vector<Texture2D> textures;
    GameManager* game;
    Map* map;

    UI(GameManager* game);

    void load_textures();
    void draw_mainUI();
    void draw_HP();
    void draw_money();
    void draw_shop();
    void drawShopItem(const Rectangle& itemRect, const Texture2D& texture, const Rectangle& textureRect, const std::string& towerType, int towerPrice);
    void draw_wave_info(WaveManager* wave);
};

#endif