#include "GameManager.hpp"

GameManager::GameManager(){
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "untitled-TD");
    ToggleFullscreen();
    SetTargetFPS(60);

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    playerHP = 100;
    money = 180;
    map = NULL;
    waveManager = NULL;
    isPlacingTower = false;
}

void GameManager::gameloop() {
    UI gameUI(this);

    while (!WindowShouldClose()) {
        // Updates
        if (waveManager != NULL) {
            waveManager->update();
        }

        if (isPlacingTower) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

                int x = map->get_tile_xPos_on_hover();
                int y = map->get_tile_yPos_on_hover();
                if (towerType == "flamethrower") {
                    towers.push_back(new flamethrower(this, map->get_tile_xPos(x) + map->get_tile_size() / 2, map->get_tile_yPos(y) + map->get_tile_size() / 2));
                }
                else if (towerType == "minigun") {
                    towers.push_back(new minigun(this, map->get_tile_xPos(x) + map->get_tile_size() / 2, map->get_tile_yPos(y) + map->get_tile_size() / 2));
                }
                else if (towerType == "basic") {
                    towers.push_back(new basicTower(this, map->get_tile_xPos(x) + map->get_tile_size() / 2, map->get_tile_yPos(y) + map->get_tile_size() / 2));
                }
                isPlacingTower = false;

                printf("%d, %d \n", x, y);
            }
        }

        for(baseTower* el : towers){
            el->update_tower();
        }
        
        for(baseProjectile* el : projectiles){
            el->update();
        }

        for(int i = 0; i < projectiles.size();){
            if(projectiles[i]->shouldDelete){
                projectiles.erase(projectiles.begin() + i);
            }
            else{
                i++;
            }
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

        for(baseProjectile* el : projectiles){
            el->draw_projectile();
        }
        
        for(baseTower* el : towers){
            el->draw_tower();
        }

        // ovo ce kasnije sve ici u jednu funckiju dw
        gameUI.draw_mainUI();
        gameUI.draw_HP();
        gameUI.draw_shop();
        gameUI.draw_money();
        EndDrawing();
    }
}

void GameManager::load_map(string mapName){
    delete waveManager;
    delete map;
    map = new Map(mapName, screenWidth / 2, screenHeight / 2, screenWidth / 2);
    if(map->loaded){
        waveManager = new WaveManager(this);
    }
}

GameManager::~GameManager(){
    delete waveManager;
    delete map;
}

void GameManager::take_damage(int damage){
    playerHP -= damage;
    if(playerHP < 0){
        playerHP = 0;
    }
    cout << "Player took damage (" << damage << ")" << " HP: " << playerHP << " $" << money << "\n";
}