#include "tiles.hpp"
#include "raylib.h"

baseTile::baseTile(){}

void baseTile::draw_tile(int posX, int posY, int size){}

void wireframeTile::draw_tile(int xPos, int yPos, int size){
    DrawRectangleLines(xPos, yPos, size, size, WHITE);
}