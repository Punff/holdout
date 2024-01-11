#include "UI.hpp"

// My hope is that this UI code is so awful that I'm never allowed to write UI code again

UI::UI(GameManager* game) {
    this->game = game;
    this->map = game->map;
    this->tileSize = map->get_tile_size();
    this->mapTiles = map->mapTiles;
    this->height = tileSize * mapTiles;
    this->width = GetScreenWidth() / 4;
    this->leftCorner = {map->get_tile_xPos(0) - width, map->get_tile_yPos(0)};
    this->rightCorner = {map->get_tile_xPos(map->mapTiles), map->get_tile_yPos(0)};
    this->padding = 15.0f;
    this->lineHeight = 30.0f;

    GuiLoadStyle("assets/style_jungle.rgs");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    GuiSetStyle(DEFAULT, BORDER_WIDTH, 5);

    load_textures();
}

void UI::load_textures() {
    textures.push_back(game->assets->load_texture("tower.png"));
    textures.push_back(game->assets->load_texture("text-tower-crossbow.png"));
    textures.push_back(game->assets->load_texture("text-tower-flamethrower.png"));
    textures.push_back(game->assets->load_texture("text-tower-artillery.png"));
    textures.push_back(game->assets->load_texture("text-tower-minigun.png"));
    textures.push_back(game->assets->load_texture("text-tower-railgun.png"));
}

void UI::draw_mainUI() {
    // Update
    Color UIGreen = {43, 58, 58, 255};
    Color UIGreener = {13, 70, 60, 255};
    // Draw
    DrawRectangleGradientEx((Rectangle) {leftCorner.x, leftCorner.y, width, height}, UIGreen, UIGreen, UIGreener, UIGreener);
    GuiGroupBox((Rectangle) {leftCorner.x, leftCorner.y, width, height}, NULL);
    DrawRectangleGradientEx((Rectangle) {rightCorner.x, rightCorner.y, width, height}, UIGreen, UIGreen, UIGreener, UIGreener);
    GuiGroupBox((Rectangle) {rightCorner.x, rightCorner.y, width, height}, NULL);
}

void UI::draw_HP() {
    // Update
    float HPvalue = game->playerHP;

    // Draw
    GuiSliderBar((Rectangle){ leftCorner.x + width / 4, leftCorner.y + lineHeight, width / 2, height / 10 }, NULL, NULL, &HPvalue, 0, 100);
}

void UI::draw_wave_info(WaveManager* wave) {
    // Update
    static int waveActive = 0;

    // Draw
    GuiGroupBox((Rectangle){ leftCorner.x, leftCorner.y + height / 4, width, height / 4 }, NULL);

    GuiValueBox((Rectangle){ leftCorner.x + width / 3, leftCorner.y + height / 4 + lineHeight, width / 3, height / 10 }, NULL, &waveActive, 0, 50, false);

    if (GuiButton((Rectangle){ leftCorner.x + width / 3, leftCorner.y + height / 2 + 3 * lineHeight, width / 3, width / 3 }, "PAUSE") && !wave->active && wave->remainingEnemies.empty()) {
        game->paused = !game->paused;
    }

    if (GuiButton((Rectangle){ leftCorner.x + width / 4, leftCorner.y + height / 4 + 5 * lineHeight, width / 2, height / 16 }, "Next wave") && !wave->active && wave->remainingEnemies.empty()) {
        if(!game->paused && wave->start_wave()){
            waveActive++;
        }
    }
}

void UI::draw_money() {
    // Update
    int moneyValue = game->money;

    // Draw
    GuiGroupBox((Rectangle){ rightCorner.x, rightCorner.y, width, height / 4 }, NULL);
    GuiValueBox((Rectangle){ rightCorner.x + width / 4, rightCorner.y + lineHeight, width / 2, height / 10 }, NULL, &moneyValue, 0, 50, false);
    DrawText("$", rightCorner.x + width / 4 + width / 2 + 10, rightCorner.y + lineHeight + height / width / 2, height / 10, DARKGRAY);
}

void UI::draw_shop() {
    // Update
    Rectangle sourceRect = {16, 0, 16, 16};
    float size = width / 4;
    float x = GetMouseX();
    float y = GetMouseY();

    Rectangle shopItem1 = { rightCorner.x + lineHeight, rightCorner.y + lineHeight + height / 4, width / 4, width / 4};
    Rectangle shopItem2 = { rightCorner.x + width / 4 + 2 * lineHeight, rightCorner.y + lineHeight + height / 4, width / 4, width / 4};
    Rectangle shopItem3 = { rightCorner.x + width / 4 + 7 * lineHeight, rightCorner.y + lineHeight + height / 4, width / 4, width / 4};
    Rectangle shopItem4 = { rightCorner.x + lineHeight, rightCorner.y + lineHeight + height / 2, width / 4, width / 4};
    Rectangle shopItem5 = { rightCorner.x + width / 4 + 2 * lineHeight, rightCorner.y + lineHeight + height / 2, width / 4, width / 4};
    Rectangle shopItem6 = { rightCorner.x + width / 4 + 7 * lineHeight, rightCorner.y + lineHeight + height / 2, width / 4, width / 4};

    // Draw
    GuiGroupBox(shopItem1, NULL);
    DrawTexturePro(textures[0], sourceRect, { shopItem1.x + padding, shopItem1.y + padding, size - padding, size - padding }, { 16 / 2, 16 / 2 }, 0, WHITE);
    DrawTexturePro(textures[0], {0, 0, 16, 16}, { shopItem1.x + padding, shopItem1.y + padding, size - padding, size - padding }, { 16 / 2, 16 / 2 }, 0, WHITE);
    if (CheckCollisionPointRec({ x, y }, shopItem1))
        DrawText(TextFormat("%d", basicTower::price), static_cast<int>(shopItem1.x) + padding, static_cast<int>(shopItem1.y) + padding, width / 6, GRAY);

    GuiGroupBox(shopItem2, NULL);
    DrawTexturePro(textures[1], {15, 0, 15, 15}, { shopItem2.x + padding, shopItem2.y + padding, size - padding, size - padding }, { 16 / 2, 16 / 2 }, 0, WHITE);
    DrawTexturePro(textures[1], {0, 0, 15, 15}, { shopItem2.x + padding, shopItem2.y + padding, size - padding, size - padding }, { 16 / 2, 16 / 2 }, 0, WHITE);
    if (CheckCollisionPointRec({ x, y }, shopItem2))
        DrawText(TextFormat("%d", crossbow::price), static_cast<int>(shopItem2.x) + padding, static_cast<int>(shopItem2.y) + padding, width / 6, GRAY);
    
    GuiGroupBox(shopItem3, NULL);
    DrawTexturePro(textures[2], {0, 0, 18, 18}, { shopItem3.x + padding, shopItem3.y + padding, size - padding, size - padding }, {18 / 2, 18 / 2}, 0, WHITE);
    if (CheckCollisionPointRec({ x, y }, shopItem3))
        DrawText(TextFormat("%d", flamethrower::price), static_cast<int>(shopItem3.x) + padding, static_cast<int>(shopItem3.y) + padding, width / 6, GRAY);

    GuiGroupBox(shopItem4, NULL);
    DrawTexturePro(textures[3], {0, 0, 16, 16}, { shopItem4.x + padding, shopItem4.y + padding, size - padding, size - padding }, { 16 / 2, 16 / 2 }, 0, WHITE);
    if (CheckCollisionPointRec({ x, y }, shopItem4))
        DrawText(TextFormat("%d", cannon::price), static_cast<int>(shopItem4.x) - 5 + padding, static_cast<int>(shopItem4.y) + 2 * padding, width / 8, GRAY);

    GuiGroupBox(shopItem5, NULL);
    DrawTexturePro(textures[4], {16, 0, 16, 16}, { shopItem5.x + padding, shopItem5.y + padding, size - padding, size - padding }, { 16 / 2, 16 / 2 }, 0, WHITE);
    DrawTexturePro(textures[4], {0, 0, 16, 16}, { shopItem5.x + padding, shopItem5.y + padding, size - padding, size - padding }, { 16 / 2, 16 / 2 }, 0, WHITE);
    if (CheckCollisionPointRec({ x, y }, shopItem5))
        DrawText(TextFormat("%d", minigun::price), static_cast<int>(shopItem5.x) - 5 + padding, static_cast<int>(shopItem5.y) + 2 * padding, width / 8, GRAY);

    GuiGroupBox(shopItem6, NULL);
    DrawTexturePro(textures[5], {64, 0, 32, 32}, { shopItem6.x + padding, shopItem6.y + padding, size - padding, size - padding }, { 16 / 2, 16 / 2 }, 0, WHITE);
    DrawTexturePro(textures[5], {0, 0, 32, 32}, { shopItem6.x + padding, shopItem6.y + padding, size - padding, size - padding }, { 16 / 2, 16 / 2 }, 0, WHITE);
    if (CheckCollisionPointRec({ x, y }, shopItem6))
        DrawText(TextFormat("%d", railgun::price), static_cast<int>(shopItem6.x) - 5 + padding, static_cast<int>(shopItem6.y) + 2 * padding, width / 8, GRAY);
    
    if(game->isPlacingTower){
        if(game->towerType == "basic"){
            DrawRectanglePro(shopItem1, {0, 0}, 0, {255, 255, 0, 100});
        }
        else if(game->towerType == "crossbow"){
            DrawRectanglePro(shopItem2, {0, 0}, 0, {255, 255, 0, 100});
        }
        else if(game->towerType == "flamethrower"){
            DrawRectanglePro(shopItem3, {0, 0}, 0, {255, 255, 0, 100});
        }
        else if(game->towerType == "cannon"){
            DrawRectanglePro(shopItem4, {0, 0}, 0, {255, 255, 0, 100});
        }
        else if(game->towerType == "minigun"){
            DrawRectanglePro(shopItem5, {0, 0}, 0, {255, 255, 0, 100});
        }
        else if(game->towerType == "railgun"){
            DrawRectanglePro(shopItem6, {0, 0}, 0, {255, 255, 0, 100});
        }
    }

    // Update

    if (GuiButton((Rectangle){ rightCorner.x + lineHeight, rightCorner.y + width / 4 + lineHeight + height / 4, width / 4 + 2, width / 4 / 4}, "Buy") && game->money >= basicTower::price) {
        game->isPlacingTower = true;
        game->towerType = "basic";
    }

    if (GuiButton((Rectangle){ rightCorner.x + width / 4 + 2 * lineHeight, rightCorner.y + width / 4 + lineHeight + height / 4, width / 4 + 2, width / 4 / 4}, "Buy") && game->money >= crossbow::price) {
        game->isPlacingTower = true;
        game->towerType = "crossbow";
    }

    if (GuiButton((Rectangle){ rightCorner.x + 2 * width / 4 + 3 * lineHeight, rightCorner.y + width / 4 + lineHeight + height / 4, width / 4 + 2, width / 4 / 4}, "Buy") && game->money >= flamethrower::price) {
        game->isPlacingTower = true;
        game->towerType = "flamethrower";
    }

    if (GuiButton((Rectangle){ rightCorner.x + lineHeight, rightCorner.y + width / 4 + lineHeight + height / 2, width / 4 + 2, width / 4 / 4}, "Buy") && game->money >= cannon::price) {
        game->isPlacingTower = true;
        game->towerType = "cannon";
    }

    if (GuiButton((Rectangle){ rightCorner.x + width / 4 + 2 * lineHeight, rightCorner.y + width / 4 + lineHeight + height / 2, width / 4 + 2, width / 4 / 4}, "Buy") && game->money >= minigun::price) {
        game->isPlacingTower = true;
        game->towerType = "minigun";
    }

    if (GuiButton((Rectangle){ rightCorner.x + 2 * width / 4 + 3 * lineHeight, rightCorner.y + width / 4 + lineHeight + height / 2, width / 4 + 2, width / 4 / 4}, "Buy") && game->money >= railgun::price) {
        game->isPlacingTower = true;
        game->towerType = "railgun";
    }
}
