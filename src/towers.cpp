#include "../include/towers.hpp"
#include "raylib.h"

baseTower::baseTower() {}

void baseTower::draw_tower(int xPos, int yPos, int size) {}
void baseTower::draw_range(int xPos, int yPos, float range) {}

void basicTower::draw_tower(int xPos, int yPos, int size) {
	DrawRectangle(xPos, yPos, size, size, WHITE);
	DrawRectangle(xPos, yPos, size - 5, size - 5, RED);
	
}

void basicTower::draw_range(int xPos, int yPos, float range) {
	DrawCircleLines(xPos, yPos, range, BLUE);
}
