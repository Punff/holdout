#include "GameManager.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {
    GameManager game;
    game.load_map("map1");
    game.gameloop();
    return 0;
}
