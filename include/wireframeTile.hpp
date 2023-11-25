#ifndef WIREFRAME_TILE_H
#define WIREFRAME_TILE_H

#include "baseTile.hpp"

class wireframeTile : public baseTile{
    void draw_tile(int xPos, int yPos, int size);
};

#endif