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
    UI gameUI(map);
    vector<basicTower> towers;

    while(!WindowShouldClose()){
        // Updates
        if(waveManager != NULL){
            waveManager->update();
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            int x = map->get_tile_xPos_on_hover();
            int y = map->get_tile_yPos_on_hover();

            basicTower tower(map->get_tile_xPos(x), map->get_tile_yPos(y));
            towers.push_back(tower);

            printf("%d, %d \n", x, y);
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
        }
        
        for (auto& tower : towers) {
            tower.update_tower(waveManager->activeEnemies, map->get_tile_size());
        }
        
        gameUI.draw_mainUI();
        gameUI.draw_wave_info(waveManager);
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
