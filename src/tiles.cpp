#include "../include/tiles.hpp"
#include "raylib.h"

// Base tile
baseTile::baseTile(){}

void baseTile::draw_tile(int xPos, int yPos, int size){}

// Wireframe tile
void wireframeTile::draw_tile(int xPos, int yPos, int size){
    DrawRectangleLines(xPos, yPos, size, size, WHITE);
}

void solidTile::draw_tile(int xPos, int yPos, int size){
    DrawRectangle(xPos, yPos, size, size, WHITE);
}