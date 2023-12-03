#include "../include/map.hpp"
#include "../include/tiles.hpp"

const string Map::MAP_PATH = "assets/maps/";

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

Map::Map(string filename){
    string path = MAP_PATH + filename + ".tmf";
    ifstream mapFile(path);
    if(!mapFile){
        cout << "Could not find " << path << "\n";
    }
    
    mapFile >> mapTiles;
    cout << "Map tiles: " << mapTiles << "\n";
    grid.resize(mapTiles);
    int tileID;

    for(int i = 0; i < mapTiles; i++)
    {
        vector<baseTile*> row(mapTiles);
        for(int j = 0; j < mapTiles; j++)
        {
            mapFile >> tileID;
            row[j] = create_tile_by_ID(tileID);
        }
        grid[i] = row;
    }

    mapFile.close();
}

baseTile* Map::create_tile_by_ID(int ID){
    switch(ID){
        case 0:
            return new wireframeTile;
        case 1:
            return new solidTile;
        default:
            return NULL;
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
            if(grid[i][j] == NULL){
                return;
            }
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
    return (size / mapTiles) * row + yPos - size / 2;
}

int Map::get_tile_size(){
    return size / mapTiles;
}

