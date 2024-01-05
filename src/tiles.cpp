#include "tiles.hpp"

// base tile

baseTile::baseTile(int xPos, int yPos, int size){
    hitbox.x = xPos;
    hitbox.y = yPos;
    hitbox.height = hitbox.width = size;
    is_path = false;
}

baseTile::~baseTile(){

}

void baseTile::draw_tile(){}

// wireframe tile
void wireframeTile::draw_tile(){
    DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, WHITE);
}

void solidTile::draw_tile(){
    DrawRectangle(hitbox.x, hitbox.y, hitbox.width, hitbox.height, WHITE);
}

// path tile
pathTile::pathTile(int xPos, int yPos, int size) : baseTile(xPos, yPos, size){
    is_path = true;
    texture = LoadTexture("assets/textures/text-tile-dirtpath.png");
}

pathTile::~pathTile(){
    UnloadTexture(texture);
}

void pathTile::draw_tile(){
    DrawTexturePro(texture, {0, 0, 16, 16}, hitbox, {0, 0}, 0, WHITE);
}
// grass tile
grassTile::grassTile(int xPos, int yPos, int size) : baseTile(xPos, yPos, size){
    texture = LoadTexture("assets/textures/text-tile-grass.png");
}

grassTile::~grassTile(){
    UnloadTexture(texture);
}

void grassTile::draw_tile(){
    DrawTexturePro(texture, {0, 0, 16, 16}, hitbox, {0, 0}, 0, WHITE);
}

