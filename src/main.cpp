#include "GameManager.hpp"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_GROUPBOX_LINE_THICK 3
#include "raygui.h"

int main() {
    GameManager game;
    game.load_map("map1");
    game.gameloop();
    return 0;
}
