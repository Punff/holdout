#ifndef TILES_H
#define TILES_H
#include "raylib.h"
class baseTile{
    public:
    Rectangle hitbox;
    baseTile(int xPos, int yPos, int size);
    virtual void draw_tile();
};

class wireframeTile : public baseTile {
    using baseTile::baseTile;
    void draw_tile();
};

class solidTile : public baseTile {
    using baseTile::baseTile;
    void draw_tile();
};

#endif
