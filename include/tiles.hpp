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
private:
    Texture2D texture;
public:
    pathTile(int xPos, int yPos, int size);
    ~pathTile();
    void draw_tile();
};

class grassTile : public baseTile {
private:
    Texture2D texture;
public:
    grassTile(int xPos, int yPos, int size);
    ~grassTile();
    void draw_tile();
};

#endif
