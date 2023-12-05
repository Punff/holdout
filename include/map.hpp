#ifndef MAP_H
#define MAP_H

#include "tiles.hpp"
#include <iostream>
#include <raylib.h>
#include <vector>
#include <fstream>
using namespace std;

class Map{
    private:
    int size, xPos, yPos, mapTiles;
    baseTile* create_tile_by_ID(int ID, int xCoord, int yCoord, int tileSize);

    public:
    static const string MAP_PATH;
    vector<vector<baseTile*>> grid;
    Map(string filename, int xPos, int yPos, int size);

    //Map(string filename);
    void draw_map();
    int get_tile_xPos(int column);
    int get_tile_yPos(int row);
    int get_tile_size();
    int get_tile_xPos_on_hover();
    int get_tile_yPos_on_hover();
};

#endif
