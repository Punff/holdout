#ifndef TILES_H
#define TILES_H

class baseTile{
    protected:
    int xPos, yPos, size;
    public:
    baseTile(int xPos, int yPos, int size);
    int get_xPos();
    int get_yPos();
    int get_size();
    virtual void draw_tile();
};

class wireframeTile : public baseTile {
    using baseTile::baseTile;
    void draw_tile();
};

#endif
