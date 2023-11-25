#ifndef BASE_TILE_H
#define BASE_TILE_H

class baseTile{
    public:
    baseTile();
    virtual void draw_tile(int xPos, int yPos, int size) = 0;
};

#endif