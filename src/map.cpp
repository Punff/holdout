#include "../include/map.hpp"
#include "../include/tiles.hpp"

Map::Map(){
    mapTiles = 10;
    grid.resize(mapTiles);
    int tileSize = size / mapTiles;

    for(int i = 0; i < mapTiles; i++){
        vector<baseTile*> row(mapTiles);
        for(int j = 0; j < mapTiles; j++){
            wireframeTile* tile = new wireframeTile(tileSize * j + xPos - size / 2, tileSize * i + yPos - size / 2, tileSize);
            row[j] = tile;
        }
        grid[i] = row;
    }
}

void Map::draw_map() {
    if(grid.size() == 0){
        return;
    }

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[0].size(); j++)
        {
            grid[i][j]->draw_tile();
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
