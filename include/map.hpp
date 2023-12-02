#ifndef MAP_H
#define MAP_H

#include "tiles.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Map{
    private:
    int size, xPos, yPos, mapTiles;

    public:
    vector<vector<baseTile*>> grid;
    Map();
    void draw_map();
    void set_size(int size);
    void set_pos(int xPos, int yPos);
};

#endif
