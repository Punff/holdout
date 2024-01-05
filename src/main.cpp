#include <iostream>
#include "map.hpp"
#include "towers.hpp"
#include "gameUI.hpp"
#include "enemies.hpp"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <vector>
#include "Vec2.hpp"
#include "waves.hpp"

using namespace std;

int main(int argc, char** argv) {
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "untitled-TD");
    ToggleFullscreen();
    SetTargetFPS(60);
    Map map("map3", GetScreenWidth() / 2, GetScreenHeight() / 2, GetScreenWidth() / 2);
    vector<basicTower> towers;
    UI testUI(&map);
    WaveManager testWave(&map);

    basicEnemy test(&map);


    while (!WindowShouldClose()) {
        // Updates

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            int x = map.get_tile_xPos_on_hover();
            int y = map.get_tile_yPos_on_hover();

            basicTower tower(map.get_tile_xPos(x), map.get_tile_yPos(y));
            towers.push_back(tower);

            printf("%d, %d \n", x, y);
        }

        testWave.update();

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(5, 5);
        map.draw_map();
        testWave.draw_enemies();
        //testWave.draw_ui();
        testUI.draw_mainUI();
        testUI.draw_wave_info(&testWave);

        for (auto& tower : towers) {
            tower.update_tower(testWave.activeEnemies, map.get_tile_size());
        }

        EndDrawing();
    }

    return 0;
}
