#ifndef TILES_H
#define TILES_H
#include "raylib.h"
class baseTile{
    public:
    Rectangle hitbox;
    bool is_path;
    baseTile(int xPos, int yPos, int size);
    virtual void draw_tile() = 0;
    virtual ~baseTile();
};

class wireframeTile : public baseTile {
    using baseTile::baseTile;
    void draw_tile();
};

class solidTile : public baseTile {
    using baseTile::baseTile;
    void draw_tile();
};

class pathTile : public baseTile {
    void draw_tile();
    public:
    pathTile(int xPos, int yPos, int size);
};

#endif
