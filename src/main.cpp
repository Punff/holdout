#include <iostream>
#include "../include/map.hpp"
#include "../include/towers.hpp"
#include "../include/gameUI.hpp"
#include <raylib.h>
#include <vector>
using namespace std;

int main(int argc, char** argv) {
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "untitled-TD");
    ToggleFullscreen();
    SetTargetFPS(60);
    Map map("map1", GetScreenWidth() / 2, GetScreenHeight() / 2, GetScreenWidth() / 2);
    vector<basicTower> towers;
    towerUI testUI(0, 0, GetScreenWidth() / 10, GetScreenHeight() / 2);


    while (!WindowShouldClose()) {
        // Updates
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            int x = map.get_tile_xPos_on_hover();
            int y = map.get_tile_yPos_on_hover();

            
            basicTower tower;
            tower.set_position(map.get_tile_xPos(x), map.get_tile_yPos(y));
            towers.push_back(tower);

            printf("%d, %d \n", x, y);
        }

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);
        DrawFPS(5, 5);
        map.draw_map();
        testUI.draw_towerUI();

        for (auto& tower : towers) {
            tower.draw_tower(map.get_tile_size());
            tower.draw_range(200, map.get_tile_size());
        }

        EndDrawing();
    }

    return 0;
}
