#ifndef MAP_H
#define MAP_H

#include "tiles.hpp"
#include <iostream>
#include <raylib.h>
#include <vector>
#include "Vec2.hpp"
#include <fstream>
using namespace std;

class GameManager;
class Map{
public:
    static const string MAP_PATH;
    int size, xPos, yPos, mapTiles;
    bool loaded;
    GameManager* game;
    baseTile* create_tile_by_ID(int ID, int xCoord, int yCoord, int tileSize);
    vector<vector<baseTile*>> grid;
    vector<Vec2> enemyPath;
    Map(string filename, int xPos, int yPos, int size, GameManager* game);

    void draw_map();
    void generate_path(Vec2 pos, Vec2 lastPos, bool start);
    int get_tile_xPos(int column);
    int get_tile_yPos(int row);
    int get_tile_size();
    float get_tile_xPos_on_hover();
    float get_tile_yPos_on_hover();
    baseTile* get_tile_at_position(int x, int y) const;
};

#endif
