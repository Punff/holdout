#include "../include/towers.hpp"
#include "raylib.h"

baseTower::baseTower() {}

void baseTower::draw_tower(int size) {}
void baseTower::draw_range(float range) {}
void baseTower::set_position(int xPos, int yPos) {
	this->xPos = xPos;
	this->yPos = yPos;
}

void basicTower::draw_tower(int size) {
	DrawRectangle(xPos, yPos, size, size, BLUE);
	//DrawRectangle(xPos, yPos, size - 5, size - 5, RED);
}

void basicTower::draw_range(float range) {
	DrawCircleLines(xPos, yPos, range, BLUE);
}

void basicTower::set_position(int xPos, int yPos) {
	baseTower::set_position(xPos, yPos);
}

