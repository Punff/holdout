#include "map.hpp"

void Map::draw_map(){
    size /= MAP_TILES;
    size *= MAP_TILES;

    int tileSize = size / MAP_TILES;
    for(int i = 0; i < MAP_TILES; i++){
        for(int j = 0; j < MAP_TILES; j++){
            grid[i][j]->draw_tile(tileSize * j + tileSize / 2, tileSize * i + tileSize / 2, tileSize);
        }
    }
}

void Map::set_size(int size){
    this->size = size;
}

void Map::set_pos(int xPos, int yPos){
    this->xPos = xPos;
    this->yPos = yPos;
}