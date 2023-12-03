#include <iostream>
#include "../include/map.hpp"
#include "../include/towers.hpp"
#include <raylib.h>
using namespace std;

int main(int argc, char** argv) {
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "raylib");
    ToggleFullscreen();
    SetTargetFPS(60);
    basicTower test;
    Map map("map1");
    
    while (!WindowShouldClose()) {
        // Updates
        map.set_size(GetScreenWidth() / 2);
        map.set_pos(GetScreenWidth() / 2, GetScreenHeight() / 2);
        basicTower test;
        
        // Draw
        BeginDrawing();
        
        ClearBackground(BLACK);
        DrawFPS(5, 5);
        map.draw_map();
        
        test.draw_tower(map.get_tile_xPos(5), map.get_tile_yPos(5), map.get_tile_size());
        test.draw_range(map.get_tile_xPos(5) + map.get_tile_size() / 2, map.get_tile_yPos(5) + map.get_tile_size() / 2, 200);
        
        EndDrawing();
    }

    return 0;
}
