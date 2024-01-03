#include "GameManager.hpp"

GameManager::GameManager(){
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "untitled-TD");
    ToggleFullscreen();
    SetTargetFPS(60);

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    playerHP = 100;
    money = 0;
    map = NULL;
    waveManager = NULL;
}

void GameManager::gameloop(){
    while(!WindowShouldClose()){
        // Updates
        if(waveManager != NULL){
            waveManager->update();
        }
        // Rendering
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(5, 5);
        if(map != NULL){
            map->draw_map();
        }
        if(waveManager != NULL){
            waveManager->draw_enemies();
            waveManager->draw_ui();
        }
        EndDrawing();
    }
}

void GameManager::load_map(string mapName){
    delete waveManager;
    delete map;
    map = new Map(mapName, screenWidth / 2, screenHeight / 2, screenWidth / 2);
    if(map->loaded){
        waveManager = new WaveManager(map);
    }
}

GameManager::~GameManager(){
    delete waveManager;
    delete map;
}
