#include "tiles.hpp"

// base tile
baseTile::baseTile(int xPos, int yPos, int size){
    hitbox.x = xPos;
    hitbox.y = yPos;
    hitbox.height = hitbox.width = size;
    is_path = false;
    is_occupied = false;
}

baseTile::~baseTile(){
    UnloadTexture(texture);
}

void baseTile::draw_tile(){
    DrawTexturePro(texture, {0, 0, 16, 16}, hitbox, {0, 0}, 0, WHITE);
}

// wireframe tile
void wireframeTile::draw_tile(){
    DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, WHITE);
}

// path tile
pathTile::pathTile(int xPos, int yPos, int size) : baseTile(xPos, yPos, size){
    is_path = true;
    is_occupied = true;
    texture = LoadTexture("assets/textures/text-tile-dirtpath.png");
}

// grass tile
grassTile::grassTile(int xPos, int yPos, int size) : baseTile(xPos, yPos, size){
    texture = LoadTexture("assets/textures/text-tile-grass.png");
}

// water tile
waterTile::waterTile(int xPos, int yPos, int size) : baseTile(xPos, yPos, size){
    texture = LoadTexture("assets/textures/text-tile-water.png");
    is_occupied = true;
}

// rock tile
rockTile::rockTile(int xPos, int yPos, int size) : baseTile(xPos, yPos, size){
    texture = LoadTexture("assets/textures/text-tile-rock-grass.png");
    is_occupied = true;
}
