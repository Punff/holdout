#include "../include/map.hpp"
#include "../include/tiles.hpp"

const string Map::MAP_PATH = "assets/maps/";

Map::Map(string filename, int xPos, int yPos, int size){
    string path = MAP_PATH + filename + ".tmf";
    ifstream mapFile(path);
    if(!mapFile){
        cout << "Could not find " << path << "\n";
        grid.clear();
        return;
    }
    
    this->xPos = xPos;
    this->yPos = yPos;
    this->size = size;
    mapFile >> mapTiles;
    grid.resize(mapTiles);
    int tileSize = get_tile_size();
    int tileID;

    for(int i = 0; i < mapTiles; i++)
    {
        vector<baseTile*> row(mapTiles);
        for(int j = 0; j < mapTiles; j++)
        {
            if(mapFile.eof()){
                cout << "Incorrect tile amount, cannot create map\n";
                grid.clear();
                return;
            }
            mapFile >> tileID;
            row[j] = create_tile_by_ID(tileID, j, i, tileSize);
        }
        grid[i] = row;
    }

    if(!mapFile.eof()){
        cout << "Warning: tile amount doesnt match map size!\n";
    }
    cout << "Map loaded\n";
    mapFile.close();
}

baseTile* Map::create_tile_by_ID(int ID, int xCoord, int yCoord, int tileSize){
    int tilexPos = xPos - size / 2 + tileSize * xCoord;
    int tileyPos = yPos - size / 2 + tileSize * yCoord;
    switch(ID){
        case 0:
            return new wireframeTile(tilexPos, tileyPos, tileSize);
        case 1:
            return new solidTile(tilexPos, tileyPos, tileSize);
        default:
            return NULL;
    }
}

void Map::draw_map() {
    if(grid.size() == 0){
        return;
    }

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[0].size(); j++)
        {
            if(grid[i][j] == NULL){
                return;
            }
            grid[i][j]->draw_tile();
        }
    }
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

int Map::get_tile_xPos_on_hover() {
    float mouseX = GetMouseX();
    float mouseY = GetMouseY();
    float tileSize = get_tile_size();

    for (int column = 0; column < mapTiles; ++column) {
        for (int row = 0; row < mapTiles; ++row) {
            float tileX = get_tile_xPos(column);
            float tileY = get_tile_yPos(row);

            Rectangle tileRect = { tileX, tileY, tileSize, tileSize };

            if (CheckCollisionPointRec({ mouseX, mouseY }, tileRect)) {
                return column;
            }
        }
    }

    return 69;
}

int Map::get_tile_yPos_on_hover() {
    float mouseY = GetMouseY();
    float mouseX = GetMouseX();
    float tileSize = get_tile_size();

    for (int column = 0; column < mapTiles; ++column) {
        for (int row = 0; row < mapTiles; ++row) {

            Rectangle tileRect = grid[row][column]->hitbox;

            if (CheckCollisionPointRec({ mouseX, mouseY }, tileRect)) {
                return row;
            }
        }
    }
    
    return 69;
}

