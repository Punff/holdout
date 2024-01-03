#include "towers.hpp"
#include "raylib.h"

baseTower::baseTower(float x, float y) {
    position = { x, y };
}

void baseTower::draw_tower(int size) {}
void baseTower::draw_range(float range, int size) {}

basicTower::basicTower(float x, float y) : baseTower(x, y) {

}

void basicTower::draw_tower(int size) {
	DrawRectangle(position.x + 15, position.y + 15, size - 30, size - 30, BLUE);
	//DrawRectangle(position.x, position.y, size - 5, size - 5, RED);
}

void basicTower::draw_range(float range, int size) {
	DrawCircleLines(position.x + size / 2, position.y + size / 2, range, ORANGE);
}
