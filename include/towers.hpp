#ifndef TOWERS_H
#define TOWERS_H
#include "../include/tiles.hpp"

class baseTower {
	protected:
	int xPos;
	int yPos;
	int HP;
	int damage;
	float range;
	int cost;
	
	public:
	// finish constructor
	baseTower();
    virtual void set_position(int xPos, int yPos);
    virtual void draw_tower(int size);
    virtual void draw_range(float range, int size);
};

class basicTower : public baseTower {
	public:
	void set_position(int xPos, int yPos);
	void draw_tower(int size);
	void draw_range(float range, int size);
};
#endif
