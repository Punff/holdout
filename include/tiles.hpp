#ifndef TILES_H
#define TILES_H

class baseTile{
    public:
    baseTile();
    virtual void draw_tile(int xPos, int yPos, int size);
};

class wireframeTile : public baseTile {
    void draw_tile(int xPos, int yPos, int size);
};

#endif
