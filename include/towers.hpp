#ifndef TOWERS_H
#define TOWERS_H
#include "../include/tiles.hpp"

class baseTower {
	protected:
	int HP;
	int damage;
	float range;
	int cost;
	
	public:
	// finish contructor
	baseTower();
    virtual void draw_tower(int xPos, int yPos, int size);
    virtual void draw_range(int xPos, int yPos, float range);
};

class basicTower : public baseTower {
	public:
	void draw_tower(int xPos, int yPos, int size);
	void draw_range(int xPos, int yPos, float range);
};
#endif
