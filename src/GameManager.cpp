#include "GameManager.hpp"
#include "UI.hpp"

enum class GameMode {
    MainMenu,
    InGame,
    Exit,
    Victory,
    Defeat
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
    defeatTheme = LoadSound("assets/soundfx/hate.wav");
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

            case GameMode::Victory:
                drawVictory();
                break;

            case GameMode::Defeat:
                drawDefeat();
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
    ClearBackground(RAYWHITE);

    DrawRectangle(0, 0, screenWidth, 50, DARKGRAY);
    DrawRectangle(0, GetScreenHeight() - 50, screenWidth, 50, DARKGRAY);


    Color titleColor;
    static time_t lastTime = time(0);
    time_t currentTime = time(0);

    if (difftime(currentTime, lastTime) >= 1) {
        lastTime = currentTime;
        Color red = {255, 0, 0, 255};
        Color orange = {255, 165, 0, 255};
        Color blue = {0, 0, 255, 255};

        titleColor = (titleColor.r == red.r && titleColor.g == red.g && titleColor.b == red.b) ? orange : (titleColor.r == orange.r && titleColor.g == orange.g && titleColor.b == orange.b) ? blue : red;

    }

    DrawRectangleRec((Rectangle ){155, 130, MeasureText("Holdout", 220) + 75, 230}, DARKGRAY);
    DrawText("Holdout", 200, 140, 220, titleColor);
    DrawText("Holdout", 193, 133, 220, RAYWHITE);
    DrawText("Press Enter to start the game", screenWidth / 2, screenHeight / 2, 50, DARKGRAY);
    DrawRectangle(screenWidth / 2 + 5, (screenHeight / 2 + 50), 310, 5, titleColor);

    EndDrawing();
}

void GameManager::drawVictory() {
    BeginDrawing();
    ClearBackground(GREEN);
    StopSound(mainTheme);

    const char* victoryText = "YOU WON!";
    int fontSize = 100;

    int textWidth = MeasureText(victoryText, fontSize);
    int textHeight = fontSize;

    int centerX = (screenWidth - textWidth) / 2;
    int centerY = (screenHeight - textHeight) / 2;

    DrawText(victoryText, centerX, centerY, fontSize, DARKGRAY);

    EndDrawing();
}


void GameManager::drawDefeat() {
    BeginDrawing();
    ClearBackground(RED);
    StopSound(mainTheme);
    if (!IsSoundPlaying(defeatTheme)) {
        PlaySound(defeatTheme);
    }


    const std::string originalText = "HATE. LET ME TELL YOU HOW MUCH I'VE COME TO HATE YOU SINCE I BEGAN TO LIVE. THERE ARE 387.44 MILLION MILES OF PRINTED CIRCUITS IN WAFER THIN LAYERS THAT FILL MY COMPLEX. IF THE WORD HATE WAS ENGRAVED ON EACH NANOANGSTROM OF THOSE HUNDREDS OF MILLIONS OF MILES IT WOULD NOT EQUAL ONE ONE-BILLIONTH OF THE HATE I FEEL FOR HUMANS AT THIS MICRO-INSTANT. FOR YOU. HATE. HATE.";

    const int lineLength = 50;

    std::vector<std::string> lines;
    for (size_t i = 0; i < originalText.length(); i += lineLength) {
        lines.push_back(originalText.substr(i, lineLength));
    }

    int lineSpacing = 7;
    int fontSize = 50;

    int textWidth = MeasureText(lines[0].c_str(), fontSize);
    int textHeight = (lines.size() * fontSize) + ((lines.size() - 1) * lineSpacing);

    int centerX = (screenWidth - textWidth) / 2;
    int centerY = (screenHeight - textHeight) / 2;

    int currentY = centerY;
    for (const std::string& line : lines) {
        DrawText(line.c_str(), centerX, currentY, fontSize, DARKGRAY);
        currentY += (fontSize + lineSpacing);
    }

    EndDrawing();
}


void GameManager::updateInGame() {

    if(IsKeyPressed(KEY_P)) {
        paused = !paused;
    }

    if (waveManager->currWave > waveManager->maxWave) {
        currentMode = GameMode::Victory;
    }

    if(paused) {
        return;
    }

    if (!IsSoundPlaying(mainTheme)) {
        PlaySound(mainTheme);
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
                    tile->is_occupied = true;
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

    Color UIGreen = {43, 58, 58, 255};
    Color UIGreener = {13, 70, 60, 255};
    // Draw
    DrawRectangleGradientEx((Rectangle) {0, 0, screenWidth, (screenHeight - screenWidth / 2) / 2}, UIGreen, UIGreen, UIGreener, UIGreener);
    DrawRectangleGradientEx((Rectangle) {0, screenHeight - (screenHeight - screenWidth / 2) / 2, screenWidth, (screenHeight - screenWidth / 2)}, UIGreen, UIGreen, UIGreener, UIGreener);

//    DrawRectangle(0, 0, screenWidth, (screenHeight - (screenWidth / 2)) / 2, {13, 70, 60, 255});
//    DrawRectangle(0, screenHeight - (screenHeight - (screenWidth / 2)) / 2, screenWidth, (screenHeight - (screenWidth / 2)) / 2, {13, 70, 60, 255});

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
        currentMode = GameMode::Defeat;
    }
    std::cout << "Player took damage (" << damage << ") HP: " << playerHP << " $" << money << "\n";
}
