#ifndef MAP_H
#define MAP_H

#include "tiles.hpp"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Map{
    private:
    int size, xPos, yPos, mapTiles;
    baseTile* create_tile_by_ID(int ID);

    public:
    static const string MAP_PATH;
    vector<vector<baseTile*>> grid;
    Map();

    Map(string filename);

    //Map(string filename);
    void draw_map();
    void set_size(int size);
    void set_pos(int xPos, int yPos);
    int get_tile_xPos(int column);
    int get_tile_yPos(int row);
    int get_tile_size();
};

#endif
