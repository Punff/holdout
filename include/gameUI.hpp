#ifndef GAMEUI_H
#define GAMEUI_H

#include <iostream>
#include <raylib.h>
using namespace std;

class towerUI {
	private:
	int xPos, yPos;
	int width, height;
	public:
	towerUI(int xPos, int yPos, int width, int height) {
		this->xPos = xPos;
		this->yPos = yPos;
		this->width = width;
		this->height = height;
	}

	void draw_towerUI();
};

class shopUI {
	
};

#endif
