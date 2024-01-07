#ifndef TILES_H
#define TILES_H

#include "raylib.h"

class baseTile {
protected:
    Texture2D texture;
public:
    int xPos;
    int yPos;
    Rectangle hitbox;
    bool is_occupied;
    bool is_path;

    baseTile(int xPos, int yPos, int size);
    virtual void draw_tile();
    virtual ~baseTile();
};

class wireframeTile : public baseTile {
    using baseTile::baseTile;
    void draw_tile();
};

class pathTile : public baseTile {
public:
    pathTile(int xPos, int yPos, int size);
};

class grassTile : public baseTile {
public:
    grassTile(int xPos, int yPos, int size);
};

class waterTile : public baseTile {
public:
    waterTile(int xPos, int yPos, int size);
};

class rockTile : public baseTile {
public:
    rockTile(int xPos, int yPos, int size);
};

#endif
