#include "tiles.hpp"
#include "raylib.h"

// Base tile
baseTile::baseTile(int xPos, int yPos, int size){
    this->xPos = xPos;
    this->yPos = yPos;
    this->size = size;
}

int baseTile::get_xPos(){
    return xPos;
}

int baseTile::get_yPos(){
    return yPos;
}

int baseTile::get_size(){
    return size;
}

void baseTile::draw_tile(){}

// Wireframe tile
void wireframeTile::draw_tile(){
    DrawRectangleLines(xPos, yPos, size, size, WHITE);
}