#include "map.hpp"
#include "wireframeTile.hpp"
#define MAP_TILES 10

Map::Map(){
    grid.resize(MAP_TILES);
    
    for(int i = 0; i < MAP_TILES; i++){
        vector<baseTile*> row(MAP_TILES);
        for(int j = 0; j < MAP_TILES; j++){
            wireframeTile* tile = new wireframeTile;
            row[j] = tile;
        }
        grid[i] = row;
    }
}

void Map::draw_map(){
    int tileSize = size / MAP_TILES;
    for(int i = 0; i < MAP_TILES; i++){
        for(int j = 0; j < MAP_TILES; j++){
            grid[i][j]->draw_tile
            (tileSize * j + tileSize / 2 + xPos - size / 2 - tileSize / 2,
            tileSize * i + tileSize / 2 + yPos - size / 2 - tileSize / 2,
            tileSize);
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
