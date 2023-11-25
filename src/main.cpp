#include <iostream>
#include "map.hpp"
#include <raylib.h>
#include <vector>
using namespace std;

int main() {
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "raylib");
    ToggleFullscreen();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Updates
        Map map;
        map.set_size(GetScreenWidth());
        map.set_poz(GetScreenWidth() / 2, GetScreenHeight() / 2);
        

        // Draw
        BeginDrawing();
        
        ClearBackground(BLACK);

        DrawRectangleLines(map.x - map.size / 2, map.y - map.size / 2, map.size, map.size, RAYWHITE);
        
        EndDrawing();
    }

    return 0;
}
