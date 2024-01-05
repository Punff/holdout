#include "GameManager.hpp"

int main() {
    GameManager game;
    game.load_map("map1");
    game.gameloop();
    return 0;
}
