#ifndef MAP_H
#define MAP_H

#include "tiles.hpp"
#include <iostream>
#include <raylib.h>
#include <vector>
#include "Vec2.hpp"
#include <fstream>
using namespace std;

class Map{
    private:
    static const string MAP_PATH;
    int size, xPos, yPos, mapTiles;
    baseTile* create_tile_by_ID(int ID, int xCoord, int yCoord, int tileSize);

    public:
    vector<vector<baseTile*>> grid;
    vector<Vec2> enemyPath;
    Map(string filename, int xPos, int yPos, int size);

    void draw_map();
    void generate_path(Vec2 pos, Vec2 lastPos, bool start);
    int get_tile_xPos(int column);
    int get_tile_yPos(int row);
    int get_tile_size();
    int get_tile_xPos_on_hover();
    int get_tile_yPos_on_hover();
};

#endif
