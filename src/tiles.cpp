#include "../include/tiles.hpp"

// Base tile

baseTile::baseTile(int xPos, int yPos, int size){
    hitbox.x = xPos;
    hitbox.y = yPos;
    hitbox.height = hitbox.width = size;
    is_path = false;
}

baseTile::~baseTile(){

}

void baseTile::draw_tile(){}

// Wireframe tile
void wireframeTile::draw_tile(){
    DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, WHITE);
}

void solidTile::draw_tile(){
    DrawRectangle(hitbox.x, hitbox.y, hitbox.width, hitbox.height, WHITE);
}

// Path tile
pathTile::pathTile(int xPos, int yPos, int size) : baseTile(xPos, yPos, size){
    is_path = true;
}

void pathTile::draw_tile(){
    DrawRectangle(hitbox.x, hitbox.y, hitbox.width, hitbox.height, BROWN);
}
