#include <iostream>
#include "map.hpp"
#include "wireframeTile.hpp"
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
        map.set_pos(GetScreenWidth() / 2, GetScreenHeight() / 2);
        

        // Draw
        BeginDrawing();
        
        ClearBackground(BLACK);

        map.draw_map();
        
        EndDrawing();
    }

    return 0;
}
