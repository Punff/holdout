#ifndef GAMEUI_H
#define GAMEUI_H

#include "raygui.h"
#include <iostream>
#include "waves.hpp"
#include <raylib.h>
#include "map.hpp"

using namespace std;

class UI {
public:
    Vec2 leftCorner, rightCorner;
    int tileSize;
    int mapTiles;
    int height;
    int width;
    int padding;
    int lineHeight;

    UI(Map* map) {
        this->tileSize = map->get_tile_size();
        this->mapTiles = map->mapTiles;
        this->height = tileSize * mapTiles;
        this->width = GetScreenWidth() / 4;
        this->leftCorner = {map->get_tile_xPos(0) - width, map->get_tile_yPos(0)};
        this->rightCorner = {map->get_tile_xPos(map->mapTiles), map->get_tile_yPos(0)};
        this->padding = 15.0f;
        this->lineHeight = 30.0f;
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
        GuiSetStyle(DEFAULT, BORDER_WIDTH, 5);

    }

	void draw_mainUI();
    void draw_HP();
    void draw_money();
    void draw_shop();
    void draw_wave_info(WaveManager* wave);
};

#endif
