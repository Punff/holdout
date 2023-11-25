#include "wireframeTile.hpp"
#include "raylib.h"

void wireframeTile::draw_tile(int xPos, int yPos, int size){
    DrawRectangleLines(xPos, yPos, size, size, WHITE);
}