#include "../include/tiles.hpp"

// Base tile

baseTile::baseTile(int xPos, int yPos, int size){
    hitbox.x = xPos;
    hitbox.y = yPos;
    hitbox.height = hitbox.width = size;
}

void baseTile::draw_tile(){}

// Wireframe tile
void wireframeTile::draw_tile(){
    DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, WHITE);
}

void solidTile::draw_tile(){
    DrawRectangle(hitbox.x, hitbox.y, hitbox.width, hitbox.height, WHITE);
}