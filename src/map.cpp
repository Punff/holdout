#include "../include/map.hpp"
#include "../include/tiles.hpp"

Map::Map(){
    mapTiles = 10;
    grid.resize(mapTiles);
    
    for(int i = 0; i < mapTiles; i++){
        vector<baseTile*> row(mapTiles);
        for(int j = 0; j < mapTiles; j++){
            wireframeTile* tile = new wireframeTile;
            row[j] = tile;
        }
        grid[i] = row;
    }
}

void Map::draw_map(){
    int tileSize = size / mapTiles;
    for(int i = 0; i < mapTiles; i++){
        for(int j = 0; j < mapTiles; j++){
            grid[i][j]->draw_tile
            (tileSize * j + xPos - size / 2,
            tileSize * i + yPos - size / 2,
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
