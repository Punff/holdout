#include "../include/map.hpp"
#include "../include/tiles.hpp"

Map::Map(){
    mapTiles = 10;
    grid.resize(mapTiles);

    for(int i = 0; i < mapTiles; i++)
    {
        vector<baseTile*> row(mapTiles);
        for(int j = 0; j < mapTiles; j++)
        {
            row[j] = new wireframeTile;
        }
        grid[i] = row;
    }
}

void Map::draw_map() {
    if(grid.size() == 0){
        return;
    }

    int tileSize = size / mapTiles;
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[0].size(); j++)
        {
            grid[i][j]->draw_tile(tileSize * j + xPos - size / 2, tileSize * i + yPos - size / 2, tileSize);
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

int Map::get_tile_xPos(int column){
    return (size / mapTiles) * column + xPos - size / 2;
}

int Map::get_tile_yPos(int row){
    return (size / mapTiles) * row + xPos - size / 2;
}

int Map::get_tile_size(){
    return size / mapTiles;
}