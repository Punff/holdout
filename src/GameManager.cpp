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
    SetTargetFPS(60);

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();
    playerHP = 100;
    money = 2500;
    map = nullptr;
    waveManager = nullptr;
    assets = new AssetServer;
    isPlacingTower = false;
    currentMode = GameMode::MainMenu;
    mainMenu = LoadSound("assets/soundfx/mainMenu.wav");
    mainTheme = LoadSound("assets/soundfx/testmusic.wav");
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
        load_map("map2");
    }
}

void GameManager::drawMainMenu() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("GlowNigger Defense", 40, 80, 150, GRAY);
    DrawText("Press Enter to start the game", screenWidth / 2, screenHeight / 2, 50, DARKGRAY);
    EndDrawing();
}

void GameManager::updateInGame() {
    if (!IsSoundPlaying(mainTheme)) {
        PlaySound(mainTheme);
    }

    if (waveManager != nullptr) {
        waveManager->update();
    }

    if (isPlacingTower) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int x = map->get_tile_xPos_on_hover();
            int y = map->get_tile_yPos_on_hover();
            int xCoord = GetMouseX();
            int yCoord = GetMouseY();

            bool canPlaceTower = true;

            for (const auto &row: map->grid) {
                for (auto &tile: row) {
                    if (CheckCollisionPointRec({(float)xCoord, (float)yCoord}, tile->hitbox)) {
                        if (!tile->is_occupied) {
                            tile->is_occupied = true;
                        } else {
                            canPlaceTower = false;
                            break;
                        }
                    }
                }
                if (!canPlaceTower) {
                    break;
                }
            }

            if (canPlaceTower) {
                if (towerType == "flamethrower") {
                    towers.push_back(new flamethrower(this, map->get_tile_xPos(x) + map->get_tile_size() / 2,
                                                      map->get_tile_yPos(y) + map->get_tile_size() / 2));
                } else if (towerType == "minigun") {
                    towers.push_back(new minigun(this, map->get_tile_xPos(x) + map->get_tile_size() / 2,
                                                 map->get_tile_yPos(y) + map->get_tile_size() / 2));
                } else if (towerType == "basic") {
                    towers.push_back(new basicTower(this, map->get_tile_xPos(x) + map->get_tile_size() / 2,
                                                    map->get_tile_yPos(y) + map->get_tile_size() / 2));
                } else if (towerType == "cannon") {
                    towers.push_back(new cannon(this, map->get_tile_xPos(x) + map->get_tile_size() / 2,
                                                    map->get_tile_yPos(y) + map->get_tile_size() / 2));
                } else if (towerType == "crossbow") {
                    towers.push_back(new crossbow(this, map->get_tile_xPos(x) + map->get_tile_size() / 2,
                                                    map->get_tile_yPos(y) + map->get_tile_size() / 2));
                } else if (towerType == "railgun") {
                    towers.push_back(new railgun(this, map->get_tile_xPos(x) + map->get_tile_size() / 2,
                                                    map->get_tile_yPos(y) + map->get_tile_size() / 2));
                }

                isPlacingTower = false;
            }
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

    gameUI->draw_mainUI();
    gameUI->draw_wave_info(waveManager);
    gameUI->draw_HP();
    gameUI->draw_shop();
    gameUI->draw_money();

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
