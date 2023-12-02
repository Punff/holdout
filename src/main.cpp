#include <iostream>
#include "../include/map.hpp"
#include "../include/tiles.hpp"
#include "../include/towers.hpp"
#include <raylib.h>
#include <vector>
using namespace std;

int main() {
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "raylib");
    ToggleFullscreen();
    SetTargetFPS(60);
    basicTower test;
    
    while (!WindowShouldClose()) {
        // Updates
        Map map;
        Map towerUI;
        map.set_size(GetScreenWidth() / 2);
        map.set_pos(GetScreenWidth() / 2, GetScreenHeight() / 2);
        int testsize = GetScreenWidth() / 2 / 10;
        // Draw
        BeginDrawing();
        
        ClearBackground(BLACK);
        DrawFPS(5, 5);
        map.draw_map();
        test.draw_tower(GetScreenWidth() / 2 + 15, GetScreenHeight() / 2 + 15, testsize - 30);
        test.draw_range(GetScreenWidth() / 2 + testsize/2, GetScreenHeight() / 2 + testsize/2, 250);
        
        EndDrawing();
    }

    return 0;
}
