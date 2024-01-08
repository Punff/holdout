#ifndef TILES_H
#define TILES_H

#include "raylib.h"

class GameManager;
class baseTile {
protected:
    Texture2D texture;
    GameManager* game;
public:
    int xPos;
    int yPos;
    Rectangle hitbox;
    bool is_occupied;
    bool is_path;

    baseTile(int xPos, int yPos, int size, GameManager* game);
    virtual void draw_tile();
    virtual ~baseTile();
};

class wireframeTile : public baseTile {
    using baseTile::baseTile;
    void draw_tile();
};

class pathTile : public baseTile {
public:
    pathTile(int xPos, int yPos, int size, GameManager* game);
};

class grassTile : public baseTile {
public:
    grassTile(int xPos, int yPos, int size, GameManager* game);
};

class waterTile : public baseTile {
public:
    waterTile(int xPos, int yPos, int size, GameManager* game);
};

class rockTile : public baseTile {
public:
    rockTile(int xPos, int yPos, int size, GameManager* game);
};

#endif
