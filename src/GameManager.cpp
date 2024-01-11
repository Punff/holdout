#include "GameManager.hpp"
#include "UI.hpp"

enum class GameMode {
    MainMenu,
    InGame,
    Exit
};

GameMode currentMode;

GameManager::GameManager() {
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "untitled-TD");
    ToggleFullscreen();
    InitAudioDevice();
    SetTargetFPS(240);

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    playerHP = 100;
    money = 80;
    paused = false;
    map = nullptr;
    waveManager = nullptr;
    assets = new AssetServer;
    isPlacingTower = false;
    currentMode = GameMode::MainMenu;
    mainMenu = LoadSound("assets/soundfx/mainMenu.wav");
    mainTheme = LoadSound("assets/soundfx/gameLoop.wav");
}

void GameManager::gameloop() {
    UI gameUI(this);
    while (!WindowShouldClose() && currentMode != GameMode::Exit) {
        switch (currentMode) {
            case GameMode::MainMenu:
                updateMainMenu();
                drawMainMenu();
                break;

            case GameMode::InGame:
                updateInGame();
                drawInGame(&gameUI);
                break;

            default:
                break;
        }
    }

    CloseWindow();
}

void GameManager::updateMainMenu() {
    if (IsKeyPressed(KEY_ENTER)) {
        PlaySound(mainMenu);
        currentMode = GameMode::InGame;
    }
}

void GameManager::drawMainMenu() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Holdout", 40, 80, 150, GRAY);
    DrawText("Press Enter to start the game", screenWidth / 2, screenHeight / 2, 50, DARKGRAY);
    EndDrawing();
}

void GameManager::updateInGame() {

    if(IsKeyPressed(KEY_P)){
        paused = !paused;
    }

    if(paused){
        return;
    }

    if (!IsSoundPlaying(mainTheme)) {
        //PlaySound(mainTheme);
    }

    if (waveManager != nullptr) {
        waveManager->update();
    }

    if (isPlacingTower && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        int x = map->get_tile_xPos_on_hover();
        int y = map->get_tile_yPos_on_hover();
        float xCoord = GetMouseX();
        float yCoord = GetMouseY();

        bool canPlaceTower = false;
        for(vector<baseTile*> row : map->grid){
            for(baseTile* tile : row){
                if(CheckCollisionPointRec({xCoord, yCoord}, tile->hitbox) && !tile->is_occupied){
                    canPlaceTower = true;
                }
            }
        }

        if (canPlaceTower && x >= 0 && y >= 0) {
            if (towerType == "flamethrower") {
                towers.push_back(new flamethrower(this, map->get_tile_xPos(x) + map->get_tile_size() / 2,
                                                    map->get_tile_yPos(y) + map->get_tile_size() / 2));
                money -= flamethrower::price;

            } else if (towerType == "minigun") {
                towers.push_back(new minigun(this, map->get_tile_xPos(x) + map->get_tile_size() / 2,
                                                map->get_tile_yPos(y) + map->get_tile_size() / 2));
                money -= minigun::price;

            } else if (towerType == "basic") {
                towers.push_back(new basicTower(this, map->get_tile_xPos(x) + map->get_tile_size() / 2,
                                                map->get_tile_yPos(y) + map->get_tile_size() / 2));
                money -= basicTower::price;

            } else if (towerType == "cannon") {
                towers.push_back(new cannon(this, map->get_tile_xPos(x) + map->get_tile_size() / 2,
                                                map->get_tile_yPos(y) + map->get_tile_size() / 2));
                money -= cannon::price;

            } else if (towerType == "crossbow") {
                towers.push_back(new crossbow(this, map->get_tile_xPos(x) + map->get_tile_size() / 2,
                                                map->get_tile_yPos(y) + map->get_tile_size() / 2));
                money -= crossbow::price;

            } else if (towerType == "railgun") {
                towers.push_back(new railgun(this, map->get_tile_xPos(x) + map->get_tile_size() / 2,
                                                map->get_tile_yPos(y) + map->get_tile_size() / 2));
                money -= railgun::price;
            }
            isPlacingTower = false;
        }
    }

    for (baseTower *el : towers) {
        el->update_tower();
    }

    for (baseProjectile *el : projectiles) {
        el->update();
    }

    for (int i = 0; i < projectiles.size();) {
        if (projectiles[i]->shouldDelete) {
            projectiles.erase(projectiles.begin() + i);
        } else {
            i++;
        }
    }

    if (IsKeyPressed(KEY_F1)) {
        currentMode = GameMode::MainMenu;
    }
}

void GameManager::drawInGame(UI* gameUI) {
    BeginDrawing();
    ClearBackground(BLANK);

    if (map != nullptr) {
        map->draw_map();
    }

    if (waveManager != nullptr) {
        waveManager->draw_enemies();
    }

    for (baseProjectile *el : projectiles) {
        el->draw_projectile();
    }

    for (baseTower *el : towers) {
        el->draw_tower();
    }

    DrawRectangle(0, 0, screenWidth / 4, screenHeight, BLACK);
    DrawRectangle(screenWidth * 3 / 4, 0, screenWidth / 4, screenHeight, BLACK);
    DrawRectangle(0, 0, screenWidth, (screenHeight - (screenWidth / 2)) / 2, BLACK);
    DrawRectangle(0, screenHeight - (screenHeight - (screenWidth / 2)) / 2, screenWidth, (screenHeight - (screenWidth / 2)) / 2, BLACK);

    gameUI->draw_mainUI();
    gameUI->draw_wave_info(waveManager);
    gameUI->draw_HP();
    gameUI->draw_shop();
    gameUI->draw_money();

    if(paused){
        DrawTexturePro(assets->load_texture("paused.png"),
        {0, 0, 31, 31},
        {(float)map->get_tile_xPos(0), (float)map->get_tile_yPos(0), (float)map->size, (float)map->size},
        {0, 0}, 0, {255, 255, 255, 200});
    }

    EndDrawing();
}

void GameManager::load_map(std::string mapName) {
    delete waveManager;
    delete map;
    map = new Map(mapName, screenWidth / 2, screenHeight / 2, screenWidth / 2, this);
    if (map->loaded) {
        waveManager = new WaveManager(this);
    }
}

GameManager::~GameManager() {
    delete waveManager;
    delete map;
}

void GameManager::take_damage(int damage) {
    playerHP -= damage;
    if (playerHP < 0) {
        playerHP = 0;
    }
    std::cout << "Player took damage (" << damage << ") HP: " << playerHP << " $" << money << "\n";
}
