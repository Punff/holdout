#include "../include/towers.hpp"
#include "raylib.h"

baseTower::baseTower() {}

void baseTower::draw_tower(int size) {}
void baseTower::draw_range(float range, int size) {}
void baseTower::set_position(int xPos, int yPos) {
	this->xPos = xPos;
	this->yPos = yPos;
}

void basicTower::draw_tower(int size) {
	DrawRectangle(xPos + 15, yPos + 15, size - 30, size - 30, BLUE);
	//DrawRectangle(xPos, yPos, size - 5, size - 5, RED);
}

void basicTower::draw_range(float range, int size) {
	DrawCircleLines(xPos + size / 2, yPos + size / 2, range, ORANGE);
}

void basicTower::set_position(int xPos, int yPos) {
	baseTower::set_position(xPos, yPos);
}

