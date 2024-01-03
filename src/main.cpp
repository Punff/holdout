#include "GameManager.hpp"

int main() {
    GameManager game;
    game.load_map("map2");
    game.gameloop();
    return 0;
}
