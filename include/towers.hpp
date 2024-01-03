#ifndef TOWERS_H
#define TOWERS_H
#include "tiles.hpp"
#include "Vec2.hpp"

class baseTower {
	protected:
    Vec2 position;
	int HP;
	int damage;
	float range;
	int cost;
	
	public:
	baseTower(float x, float y);
    virtual void draw_tower(int size);
    virtual void draw_range(float range, int size);
};

class basicTower : public baseTower {
	public:
    basicTower(float x, float y);
	void draw_tower(int size) override;
	void draw_range(float range, int size) override;
};
#endif
